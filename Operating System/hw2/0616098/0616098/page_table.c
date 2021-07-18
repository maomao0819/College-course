#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "page_table_driver.h"

int fd;

// Obtain my cr3 value (a.k.a. PML4 table physical address)
uint64_t get_cr3_value()
{
	struct ioctl_arg cmd;
	int ret;
	cmd.request[0] = IO_CR3;
	ret = ioctl(fd, IOCTL_REQUEST, &cmd);
	return cmd.ret;
}

// Given a physical address, return the value
uint64_t read_physical_address(uint64_t physical_address)
{
	struct ioctl_arg cmd;
	int ret;
	cmd.request[0] = IO_READ;
	cmd.request[1] = physical_address;
	ret = ioctl(fd, IOCTL_REQUEST, &cmd);
	return cmd.ret;
}

// Write value to a physical address
void write_physical_address(uint64_t physical_address, uint64_t value)
{
	struct ioctl_arg cmd;
	int ret;
	cmd.request[0] = IO_WRITE;
	cmd.request[1] = physical_address;
	cmd.request[2] = value;
	ret = ioctl(fd, IOCTL_REQUEST, &cmd);
}

int main()
{
	char *x = (char*)aligned_alloc(4096, 4096) + 0x123;
	char *y = (char*)aligned_alloc(4096, 4096) + 0x123;
	strcpy(x, "This is a simple HW.");
	strcpy(y, "You have to modify my page table.");

	fd = open("/dev/os", O_RDONLY);
	if(fd < 0) 
	{
		printf("Cannot open device!\n");
		return 0;
	}

	printf("Before\n");
	printf("x : %s\n", x);
	printf("y : %s\n", y);
	/* TODO 1 */
	// ------------------------------------------------
	// Modify page table entry of y
	// Let y point to x's physical address
	// ------------------------------------------------
	uint64_t cr3 = get_cr3_value();
	
	uint64_t x_address = x;
	uint64_t x_offset = x_address & 0xfff;
	uint64_t x_shifted_address = x_address >> 12;
	uint64_t x_pte_offset = (x_shifted_address & 0x1ff);
	x_shifted_address = x_shifted_address >> 9;
	uint64_t x_pde_offset = x_shifted_address & 0x1ff;
	x_shifted_address = x_shifted_address >> 9;
	uint64_t x_pdpe_offset = x_shifted_address & 0x1ff;
	x_shifted_address = x_shifted_address >> 9;
	uint64_t x_pml4e_offset = x_shifted_address & 0x1ff;
		
	uint64_t x_PML4 = (cr3 >> 12 << 12) | (x_pml4e_offset << 3);
	uint64_t x_PDPT = (read_physical_address(x_PML4) & 0xffffff000) | (x_pdpe_offset << 3);	
	uint64_t x_PD = (read_physical_address(x_PDPT) & 0xffffff000) | (x_pde_offset << 3);
	uint64_t x_PT = (read_physical_address(x_PD) & 0xffffff000) | (x_pte_offset << 3);
	uint64_t x_physical_addr = (read_physical_address(x_PT) & 0xfffffffff) + x_offset;

	uint64_t y_address = y;
	uint64_t y_offset = y_address & 0xfff;
	uint64_t y_shifted_address = y_address >> 12;
	uint64_t y_pte_offset = (y_shifted_address & 0x1ff);
	y_shifted_address = y_shifted_address >> 9;
	uint64_t y_pde_offset = y_shifted_address & 0x1ff;
	y_shifted_address = y_shifted_address >> 9;
	uint64_t y_pdpe_offset = y_shifted_address & 0x1ff;
	y_shifted_address = y_shifted_address >> 9;
	uint64_t y_pml4e_offset = y_shifted_address & 0x1ff;

	uint64_t y_PML4 = (cr3 >> 12 << 12) | (y_pml4e_offset << 3);
	uint64_t y_PDPT = (read_physical_address(y_PML4) & 0xffffff000)  | (y_pdpe_offset << 3);	
	uint64_t y_PD = (read_physical_address(y_PDPT) & 0xffffff000)  | (y_pde_offset << 3);
	uint64_t y_PT = (read_physical_address(y_PD) & 0xffffff000)  | (y_pte_offset << 3);
	
	uint64_t y_physical_addr = (read_physical_address(y_PT) & 0xfffffffff) + y_offset;

	write_physical_address(y_PT, x_physical_addr - y_offset);

	getchar();

	printf("After modifying page table\n");
	printf("x : %s\n", x);
	printf("y : %s\n", y);

	getchar();

	strcpy(y, "When you modify y, x is modified actually.");
	printf("After modifying string y\n");
	printf("x : %s\n", x);
	printf("y : %s\n", y);

	/* TODO 2 */
	// ------------------------------------------------
	// Recover page table entry of y
	// Let y point to its original address
	// You may need to store y's original address at previous step
	// ------------------------------------------------
	write_physical_address(y_PT, y_physical_addr - y_offset);

	getchar();

	printf("After recovering page table of y\n");
	printf("x : %s\n", x);
	printf("y : %s\n", y);

	close(fd);
}

