select P.Id, avg(P.kills) as avgKills
from player_statistic P, `match` M
where M.numGroups <= 10 and M.matchId = P.matchId
group by P.Id
order by  avg(P.kills) desc
limit 20;