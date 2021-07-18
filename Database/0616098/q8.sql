select P.roadKills as teamRoadKills, avg(P.winPlacePerc) as avgWinPlacePerc
from `match` M, player_statistic P
where M.matchType = "squad" or M.matchType = "squad-fpp" and M.matchId = P.matchId
group by P.roadKills
order by 2;

