#!/usr/bin/perl -w

package WgetTest;
$VERSION = 0.01;

use strict;

use Cwd;
use File::Path;

our $WGETPATH = "../../wget-1.11.4-src/src/wget";

my @unexpected_downloads = ();

{
    my %_attr_data = ( # DEFAULT
        _cmdline      => "",
        _workdir      => Cwd::getcwd(),
        _errcode      => 0,
        _existing     => {},
        _input        => {},
        _name         => "",
        _output       => {},
    );
    
    sub _default_for
    {
        my ($self, $attr) = @_;
        $_attr_data{$attr};
    }

    sub _standard_keys 
    {
        keys %_attr_data;
    }
}


sub new {
    my ($caller, %args) = @_;
    my $caller_is_obj = ref($caller);
    my $class = $caller_is_obj || $caller;
    #print STDERR "class = ", $class, "\n";
    #print STDERR "_attr_data {workdir} = ", $WgetTest::_attr_data{_workdir}, "\n";
    my $self = bless {}, $class;
    foreach my $attrname ($self->_standard_keys()) {
        #print STDERR "attrname = ", $attrname, " value = ";
        my ($argname) = ($attrname =~ /^_(.*)/);
        if (exists $args{$argname}) {
            #printf STDERR "Setting up $attrname\n";
            $self->{$attrname} = $args{$argname};
        } elsif ($caller_is_obj) {
            #printf STDERR "Copying $attrname\n";
            $self->{$attrname} = $caller->{$attrname};
        } else {
            #printf STDERR "Using default for $attrname\n";
            $self->{$attrname} = $self->_default_for($attrname);
        }
        #print STDERR $attrname, '=', $self->{$attrname}, "\n";
    }
    #printf STDERR "_workdir default = ", $self->_default_for("_workdir");
    return $self;
}


sub run {
    my $self = shift;
    my $result_message = "Test successful.\n";
   
    printf "Running test $self->{_name}\n";
    
    # Setup 
    $self->_setup();
    chdir ("$self->{_workdir}/$self->{_name}/input");
    
    # Launch server
    my $pid = $self->_fork_and_launch_server();
    
    # Call wget
    chdir ("$self->{_workdir}/$self->{_name}/output");
    # print "Calling $self->{_cmdline}\n";
    my $errcode = 
        ($self->{_cmdline} =~ m{^/.*}) 
            ? system ($self->{_cmdline})
            : system ("$self->{_workdir}/../src/$self->{_cmdline}");

    # Shutdown server
    # if we didn't explicitely kill the server, we would have to call 
    # waitpid ($pid, 0) here in order to wait for the child process to 
    # terminate
    kill ('TERM', $pid);

    # Verify download
    unless ($errcode == $self->{_errcode}) {
        $result_message = "Test failed: wrong code returned (was: $errcode, expected: $self->{_errcode})\n";
    }
    my $error_str;
    if ($error_str = $self->_verify_download()) {
        $result_message = $error_str;
    }

    # Cleanup
    $self->_cleanup();

    print $result_message;
    return $errcode != $self->{_errcode} || ($error_str ? 1 : 0);
}


sub _setup {
    my $self = shift;

    #print $self->{_name}, "\n";
    chdir ($self->{_workdir});

    # Create temporary directory
    mkdir ($self->{_name});
    chdir ($self->{_name});
    mkdir ("input");
    mkdir ("output");
    
    # Setup existing files
    chdir ("output");
    foreach my $filename (keys %{$self->{_existing}}) {
        open (FILE, ">$filename") 
            or return "Test failed: cannot open pre-existing file $filename\n";

        my $file = $self->{_existing}->{$filename};
        print FILE $file->{content}
            or return "Test failed: cannot write pre-existing file $filename\n";

        close (FILE);

        if (exists($file->{timestamp})) {
            utime $file->{timestamp}, $file->{timestamp}, $filename
                or return "Test failed: cannot set timestamp on pre-existing file $filename\n";
        }
    } 
    
    chdir ("../input");
    $self->_setup_server();

    chdir ($self->{_workdir});
}


sub _cleanup {
    my $self = shift;

    chdir ($self->{_workdir});
    File::Path::rmtree ($self->{_name});
}


sub _verify_download {
    my $self = shift;

    chdir ("$self->{_workdir}/$self->{_name}/output");
    
    # use slurp mode to read file content
    my $old_input_record_separator = $/;
    undef $/;
    
    while (my ($filename, $filedata) = each %{$self->{_output}}) {
        open (FILE, $filename) 
            or return "Test failed: file $filename not downloaded\n";
        
        my $content = <FILE>;
        $content eq $filedata->{'content'} 
            or return "Test failed: wrong content for file $filename\n";

        if (exists($filedata->{'timestamp'})) {
            my ($dev, $ino, $mode, $nlink, $uid, $gid, $rdev, $size,
                $atime, $mtime, $ctime, $blksize, $blocks) = stat FILE;

            $mtime == $filedata->{'timestamp'} 
                or return "Test failed: wrong timestamp for file $filename\n";
        }
        
        close (FILE);
    } 
    
    $/ = $old_input_record_separator;    

    # make sure no unexpected files were downloaded
    chdir ("$self->{_workdir}/$self->{_name}/output");

    __dir_walk('.', sub { push @unexpected_downloads, $_[0] unless (exists $self->{_output}{$_[0]}) }, sub { shift; return @_ } );
    if (@unexpected_downloads) { 
        return "Test failed: unexpected downloaded files [" . join(', ', @unexpected_downloads) . "]\n";
    }

    return "";
}


sub __dir_walk {
    my ($top, $filefunc, $dirfunc) = @_;

    my $DIR;

    if (-d $top) {
        my $file;
        unless (opendir $DIR, $top) {
            warn "Couldn't open directory $DIR: $!; skipping.\n";
            return;
        }

        my @results;
        while ($file = readdir $DIR) {
            next if $file eq '.' || $file eq '..';
            my $nextdir = $top eq '.' ? $file : "$top/$file";
            push @results, __dir_walk($nextdir, $filefunc, $dirfunc);
        }

        return $dirfunc ? $dirfunc->($top, @results) : () ;
    } else {
        return $filefunc ? $filefunc->($top) : () ;
    }
}


sub _fork_and_launch_server 
{
    my $self = shift;

    pipe(FROM_CHILD, TO_PARENT) or die "Cannot create pipe!";
    select((select(TO_PARENT), $| = 1)[0]);

    my $pid = fork();
    if ($pid < 0) {
        die "Cannot fork";
    } elsif ($pid == 0) {
        # child 
        close FROM_CHILD;
        $self->_launch_server(sub { print TO_PARENT "SYNC\n"; close TO_PARENT });
    } else {
        # father
        close TO_PARENT;
        chomp(my $line = <FROM_CHILD>);
        close FROM_CHILD;
    }

    return $pid;
}

1;

# vim: et ts=4 sw=4

