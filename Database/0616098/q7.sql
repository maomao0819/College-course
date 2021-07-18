select count(*) as numberOFplayers, max(P.heals) as MaxHeals
from `match` M, player_statistic P
where P.damageDealt = 0 and M.matchId = P.matchId and
		 M.matchDuration > (select avg(M2.matchDuration)
								from `match` M2); 

