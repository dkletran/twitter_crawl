export LD_LIBRARY_PATH=/opt/boost/boost_1_50_0/lib/
while true
do
./Release/put_links
./Release/put_statuses_authors

echo "wait 1h to restart put_links and put_statuses_authors"
sleep 3600

done
