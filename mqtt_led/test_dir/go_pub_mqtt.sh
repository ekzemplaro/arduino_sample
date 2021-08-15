#
#BROKER="mqtt.eclipse.org"
#BROKER="test.mosquitto.org"
BROKER="broker.emqx.io"
#
echo $BROKER
message='{"led": "green"}'
mosquitto_pub -d -t orz -m "${message}" \
    -h  $BROKER \
    --topic example/testTopic
#
