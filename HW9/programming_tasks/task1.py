import netifaces as ni

info = ni.ifaddresses('wlp2s0')[ni.AF_INET][0]
print('ip =', info['addr'])
print('netmask =', info['netmask'])