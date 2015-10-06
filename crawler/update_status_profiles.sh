export LD_LIBRARY_PATH=/opt/boost/boost_1_50_0/lib/

while true
do

./Release/get_favourites --username dkletran --password taolatao --proxy-port 3128 --proxy-host 10.193.21.180 --consumer-key NWqNyXhmlwJo5BRtwnWRQ --consumer-secret TOBM19autzHGgdlAQGtavei6V5Hc74h3sFg0jLcQ --crawl-max-retry 4 --crawling-depth 100
echo "wait 0 minutes to start get_status_profile"
#sleep 720
./Release/get_status_profiles --username dkletran --password taolatao --proxy-port 3128 --proxy-host 10.193.21.180 --consumer-key NWqNyXhmlwJo5BRtwnWRQ --consumer-secret TOBM19autzHGgdlAQGtavei6V5Hc74h3sFg0jLcQ --crawl-max-retry 5 --crawling-depth 100
echo "wait 0 minutes to start get_favourites"
#sleep 720
done
