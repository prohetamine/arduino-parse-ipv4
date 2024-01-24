void setup() {
  Serial.begin(115200);
}

int sort_desc(const void *cmp1, const void *cmp2) {
  int a = *((int *)cmp1);
  int b = *((int *)cmp2);
  return a > b ? -1 : (a < b ? 1 : 0);
}

int multiIndexOf (String str, String allow[], int allowCount, int i) {
  int data[allowCount] = {};
  int dataReverse[allowCount] = {};

  for (int x = 0; x < allowCount; x++) {
    data[x] = str.indexOf(allow[x], i);

    if (data[x] == -1) {
      data[x] = 9999;
    }
  }

  int data_length = sizeof(data) / sizeof(data[0]);
  qsort(data, data_length, sizeof(data[0]), sort_desc);

  int x = 0;

  while (data_length) {
    dataReverse[x] = data[data_length];
    x++;
    data_length--;
  }

  return dataReverse[1];
}

String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

String parseIpv4 (String str) {
  String allow[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "." };
  String allowNumbers[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

  for (int x = 0; x < str.length(); x++) {
    int a = multiIndexOf((String)str[x], allowNumbers, 10, 0);
    int b = multiIndexOf((String)str[x+1], allowNumbers, 10, 0);
    int c = multiIndexOf((String)str[x+2], allowNumbers, 10, 0);
    int d = ((String)str[x+3]).indexOf(".", 0);
    int e = multiIndexOf((String)str[x+4], allowNumbers, 10, 0);

    if (
      c != 9999 &&
      d != 9999 &&
      e != 9999 &&
      c == d && 
      d == e 
    ) {
      int offset = -2;

      if (b != 9999) {
        offset = -1;  
      }

      if (a != 9999 && b != 9999) {
        offset = 0; 
      }

      int m = multiIndexOf(str, allow, 11, x - offset);

      String ip = str.substring(m, m + 15);
      
      int first = ip.indexOf(".", 0);

      if (first != -1) {
        int two = ip.substring(first + 1).indexOf(".");

        if (two != -1) {
          int three = ip.substring(two + 1).indexOf(".");

          if (three != -1) {
            if (multiIndexOf((String)ip[0], allowNumbers, 10, 0) != 9999) {
              String _ip = "";

              for (int l = 0; l < ip.length(); l++) {
                if (multiIndexOf((String)ip[l], allow, 11, 0) != 9999) {
                  _ip += ip[l];                   
                } else {
                  break;
                }
              }

              String ipPart1 = getValue(_ip, '.', 0);
              String ipPart2 = getValue(_ip, '.', 1);
              String ipPart3 = getValue(_ip, '.', 2);
              String ipPart4 = getValue(_ip, '.', 3);
              
              if (ipPart1 && ipPart2 && ipPart3 && ipPart4) {
                int ipPartInt1 = ipPart1.toInt();
                int ipPartInt2 = ipPart2.toInt();
                int ipPartInt3 = ipPart3.toInt();
                int ipPartInt4 = ipPart4.toInt();

                if (
                  (ipPartInt1 >= 0 && ipPartInt1 <= 255) &&
                  (ipPartInt2 >= 0 && ipPartInt2 <= 255) &&
                  (ipPartInt3 >= 0 && ipPartInt3 <= 255) &&
                  (ipPartInt4 >= 0 && ipPartInt4 <= 255)
                ) {
                  if (
                    (String)ipPartInt1 == ipPart1 && 
                    (String)ipPartInt2 == ipPart2 && 
                    (String)ipPartInt3 == ipPart3 && 
                    (String)ipPartInt4 == ipPart4
                  ) {
                    return ipPart1 + "." + ipPart2 + "." + ipPart3 + "." + ipPart4;
                  }
                }
              }
            }          
          }
        }
      }
    }
  }

  return "";
}


void loop() {
  String strValid1 = "Hello world 221 1.1.1.1 ghtuyuyggghj";
  String strValid2 = "Hello world 221 255.255.255.255 ghtuyuyggghj";
  String strValid3 = "Hello world 221 88.88.88.88 ghtuyuyggghj";
  String strValid4 = "Hello world 221 0.0.0.0 123 ghtuyuyggghj";
  String strValid5 = "Hello world 221 \"0.0.0.0\" 123 ghtuyuyggghj";
  String strValid6 = "{\"ip\":\"192.168.1.1\"}";

  String strInvalid1 = "Hello world 255 ghtuyuyggghj";
  String strInvalid2 = "Hello world 221 0.0.0.023 ghtuyuyggghj";
  String strInvalid3 = "Hello world 2210.02123123.0.023 ghtuyuyggghj";

  String ip1 = parseIpv4(strValid1);
  String ip2 = parseIpv4(strValid2);
  String ip3 = parseIpv4(strValid3);
  String ip4 = parseIpv4(strValid4);
  String ip5 = parseIpv4(strValid5);
  String ip6 = parseIpv4(strValid6);
  String ip7 = parseIpv4(strInvalid1);
  String ip8 = parseIpv4(strInvalid2);
  String ip9 = parseIpv4(strInvalid3);

  Serial.println("VALID [ " + strValid1 + " ] >>> [ " + ip1 + " ]");
  Serial.println("VALID [ " + strValid2 + " ] >>> [ " + ip2 + " ]");
  Serial.println("VALID [ " + strValid3 + " ] >>> [ " + ip3 + " ]");
  Serial.println("VALID [ " + strValid4 + " ] >>> [ " + ip4 + " ]");
  Serial.println("VALID [ " + strValid5 + " ] >>> [ " + ip5 + " ]");
  Serial.println("VALID [ " + strValid6 + " ] >>> [ " + ip6 + " ]");
  Serial.println("INVALID [ " + strInvalid1 + " ] >>> [ " + ip7 + " ]");
  Serial.println("INVALID [ " + strInvalid2 + " ] >>> [ " + ip8 + " ]");
  Serial.println("INVALID [ " + strInvalid3 + " ] >>> [ " + ip9 + " ]");
  Serial.println("------------");

  delay(1000);
}
