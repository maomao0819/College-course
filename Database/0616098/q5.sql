select matchType, avg (matchDuration) as averageDuration
from `match` 
group by matchType
order by  2;