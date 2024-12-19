#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "ESP"                         //change this
 
//const char WIFI_SSID[] = "ORLANDO";               //change this
//const char WIFI_PASSWORD[] = "12345678";           //change this
const char AWS_IOT_ENDPOINT[] = "a30lo353syqta8-ats.iot.us-east-2.amazonaws.com";     
// Amazon Root CA 1 este no se mueve
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAMudd1969W1mCPWcHJQoFoU9CMAYMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMzExMDYxNzMy
MzRaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDXMqCTMRVQDNtyHev8
KyLQzATkg5siMTfh3SZBpzzDTxuShQ39UQueYPxcsAFYeAGmpKE2Z8h8G7WyYnw7
hrHFPQQEZ6yO0P06bAH3M6DVkMuCo0A7AciJhUsG513lifXBKHJJyiut0JD4WZLj
Hlf9WSbeJqLdf5nwicsP3Zjrcu9J8JMGoelQXh2Ms3NV+THlhKrg/8P/1x8rSCen
mHLTlln55ZdN94r21UO8RKXV1V4favXPPXQJHwn09Nh7K7N9NqzLFQIK9FQMaAnp
OSD9A1HgrKs5H5joyQljNQr5VAcrM1LAu6NCC3FdKWH4ezelNXUvOm3K+pcOWX9X
LJ1zAgMBAAGjYDBeMB8GA1UdIwQYMBaAFCxGOq4EfVl9O0++pQ4jpQrqygQ8MB0G
A1UdDgQWBBRg1nhr2tgkr7sa3WFpy9f+Q4D+pjAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAhAB7gIfx3FN0EgHhFJ0dyWtg
E9/isv8Uig35qsKtcVrpWyA0K8aAIV3y8yK0EdAeBrz49SQmwvt+s3lLBf2hNh2n
VCoBhHZgOMtkyynn/KPfisFQXNYzMR74saSQk01N0xtfq/jCJJFbPkl4YBKWiYBQ
5fqQooTW/AAfh4RzE8tpq16JuxzFg5+u4POe6ymRcVbG2zwdhb1IEiUo6hF8KURI
YM3DXE7x2m3J8Sn4viBEB0pFtLl9k+p4b12DO3zAFLr/R1UHraUgZOos+aoSvlQ7
lMh1XPhDDlObgzkfciSstAzXt0vKt4V8ApcVuh1ZxE3iZ9G6Fcb4cBmZZV8AxA==
-----END CERTIFICATE-----
)KEY";
// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpgIBAAKCAQEA1zKgkzEVUAzbch3r/Csi0MwE5IObIjE34d0mQac8w08bkoUN
/VELnmD8XLABWHgBpqShNmfIfBu1smJ8O4axxT0EBGesjtD9OmwB9zOg1ZDLgqNA
OwHIiYVLBudd5Yn1wShyScorrdCQ+FmS4x5X/Vkm3iai3X+Z8InLD92Y63LvSfCT
BqHpUF4djLNzVfkx5YSq4P/D/9cfK0gnp5hy05ZZ+eWXTfeK9tVDvESl1dVeH2r1
zz10CR8J9PTYeyuzfTasyxUCCvRUDGgJ6Tkg/QNR4KyrOR+Y6MkJYzUK+VQHKzNS
wLujQgtxXSlh+Hs3pTV1LzptyvqXDll/VyydcwIDAQABAoIBAQC88tfoxXUIJ3Ha
/gjBDgLwv+If3qos2HhPmcTIapXAi0oTWT5SSIHiGxgaLfPQgPY6IlzmjzOKPS5J
JY4dGgQmwY8wavMpJrjhPgpvyeYS/qKh3sM7zDIPBXk945IfRAYDBodq4Nd/MxzG
4qdFQdRSP6AP+G6R+0Ln36TrFk/5kgHW0efQl72y94zchL8zj0inkplEavKtfBTN
/eEnfeqazyTo2WhemQfjasdddxKQsTH+zddyw05GBRkbnpwXDZ26YXx7AVRpint3
ys8mKfcq68wexQyKOO1DGy4NN7JKWxAYBlrJCBXugNVld+wspgNVvlA0rqboc3Ow
SRvJ2D9RAoGBAPDZfauJRi32yictaBDlqYIaD5qE9CVbMevUi9GEXsPWyuWw2rEU
qTfQ+lSCiKNfexpuFZqWnFIHMsJOrS/58AYCi3MgYnwwhLfT1x2NYZSDaElSIPxW
1xHg2QzgucNibh0pOPhL8Zk87e24B5DEeVw8pZHTMX7CLjhBNvSQf1Y5AoGBAOS8
Db5ZVoZ/uKX6ETC+ZTEEQAjL43EVxGhtNCpfZUpsKfHOHFHtC+a+yk4/Ux1Ud3/K
zKIcY6UpmuM9hQyVR+rbANN+DLCzYCVgsGPmPr9Fv/+rgcLGBIiYy1zdkYD6tfrv
aTFY3mtig/MK9vw7+7Mu3LF4XICwbMFMyV57yzELAoGBAI1nU6X7YW2pAATCXt/U
xpFw1Ypl1qV8BjIsRq6K5cxa9iKmk671r2fq1J37SVeJvk/FI//vvvVV7pIv+PQ6
7JXKtq6v68J4BeObhyd9kzXLdNXfVyhvn7OKbERoSAgTaQzL3/u/MqhCInq32hE/
mPTzUk3sTZnbTaGPgEFT+L7ZAoGBAKSCOCRCHsAHVidRrlFvbloNo3xwH7mynRs6
B32+NJyNJLG7upSVt6ySZfBXDREYMgYgNoMVhflA7hwnn+yH5TydnH9/teLUb/8S
BmsjKtfoc4mPsXkDcDlKI2E8Hi00o/PBgteyAe4b4ajIpxCMl5+swZ+GYIlR2jZA
YsfooyA3AoGBAM6sxkkRpE8tuRk9Nbs1jmHWyr2PyC5nlcM01fRPd6Q23Ngh0ULX
Np6n4+f8mqcdPkqWw+/aU81cZK7ktDCrnDzd2hXBPSV9uIRQ6UXdjBcK7HPripja
vkkHQr/dK/kVmNKnRFeb+0V8bCmCkNxSWz6bquEazEhrLZahJAJ1aLOX
-----END RSA PRIVATE KEY-----
)KEY";
