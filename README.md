Parsing the v4 IP address in a string for esp32, esp8266-12, esp8266-07, esp8266-01, Arduino Nano, Arduino UNO and etc

------------

VALID [ Hello world 221 1.1.1.1 ghtuyuyggghj ] >>> [ 1.1.1.1 ]

VALID [ Hello world 221 255.255.255.255 ghtuyuyggghj ] >>> [ 255.255.255.255 ]

VALID [ Hello world 221 88.88.88.88 ghtuyuyggghj ] >>> [ 88.88.88.88 ]

VALID [ Hello world 221 0.0.0.0 123 ghtuyuyggghj ] >>> [ 0.0.0.0 ]

VALID [ Hello world 221 "0.0.0.0" 123 ghtuyuyggghj ] >>> [ 0.0.0.0 ]

VALID [ {"ip":"192.168.1.1"} ] >>> [ 192.168.1.1 ]

INVALID [ Hello world 255 ghtuyuyggghj ] >>> [  ]

INVALID [ Hello world 221 0.0.0.023 ghtuyuyggghj ] >>> [  ]

INVALID [ Hello world 2210.02123123.0.023 ghtuyuyggghj ] >>> [  ]

------------
