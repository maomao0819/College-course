select walkDistance + swimDistance + rideDistance as totalDistance, walkDistance, swimDistance, rideDistance 
from player_statistic 
where walkDistance > 0 and swimDistance > 0 and rideDistance > 0
order by  totalDistance desc
limit 10;