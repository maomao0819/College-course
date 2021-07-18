select matchType, count(*) as count
from `match`
where matchType like '%fpp%'
group by matchType
order by  2;