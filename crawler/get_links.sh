export LD_LIBRARY_PATH=/opt/boost/boost_1_50_0/lib/
while true
do


./Release/get_links --username dkletran --password taolatao --proxy-port 3128 --proxy-host 10.193.21.180 --consumer-key NWqNyXhmlwJo5BRtwnWRQ --consumer-secret TOBM19autzHGgdlAQGtavei6V5Hc74h3sFg0jLcQ  --crawling-depth 100 --users-count 99999
echo "wait 5 jours to restart get_links"
sleep 432000 

done
