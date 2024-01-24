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

String parseIpv4 (String str) {
  String allow[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "." };
  String allowNumbers[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

  for (int x = 0; x < str.length(); x++) {
    int a = multiIndexOf(str, allowNumbers, 10, x);
    int b = str.indexOf(".", x+1);
    int c = multiIndexOf(str, allowNumbers, 10, x+2);

    if (
      a != 9999 &&
      b != 9999 &&
      c != 9999 &&
      a == b - 1 && 
      b == c - 1
    ) {
      int a = multiIndexOf(str, allow, 11, x-2);

      String ip = str.substring(a, a + 15);
      
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
                }
              }

              return _ip;
            }          
          }
        }
      }
    }
  }

  return "";
}


void loop() {
  String str = "Hello world 221 143.122.212.122 ghtuyuyggghj ";

  String ip = parseIpv4(str);

  Serial.println(ip);
}
