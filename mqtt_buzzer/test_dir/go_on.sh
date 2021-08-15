#
# BROKER="broker.emqx.io"
BROKER="test.mosquitto.org"
#
echo $BROKER
message='{"buzzer": "on"}'
mosquitto_pub -d -t orz -m "${message}" \
    -h  $BROKER --topic example/testTopic
#
