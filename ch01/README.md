## Exercise 1.1

这里网址(ftp.rfc.editor.org)失效，现在为ftp://ftp.rfc-editor.org/


## Exercise 1.3

(a) (2*50ms)+(1000KB/1.5Mbps)+50ms/2=5.46s

(b) a中的结果加上1000KB/1KB个分组发送的时间，即加上1000*50ms,为55.46s

(c) (1000/20)*50ms=2.5s

(d) 1+2+4+8+...+2^(n-1)+... >=1000 几何级数，sum=2^n-1, n=log(1001)向上取整，n=10


## Exercise 1.5
Propagration=Distance/Speed=4000m/(2*10^8)s=2*10^(-5)s
由Bandwidth=Size/Transmit，Transmit=Propagation得
a) Size=100Byte时，Bandwidth=100Byte/2*10^(-5)s=5*10^6Byte/s
b) Size=512Byte时，Bandwidth=512Byte/2*10^(-5)s=25.6*10^6Byte/s
