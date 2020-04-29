#include "SerialClient.h"

int SerialClient::set_interface_attribs(int speed, int parity)
{
  struct termios tty;
  if (tcgetattr (tty_file, &tty) != 0)
  {
    Serial.printf("error %d from tcgetattr", errno);
    return -1;
  }

  cfsetospeed (&tty, speed);
  cfsetispeed (&tty, speed);

  tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
  // disable IGNBRK for mismatched speed tests; otherwise receive break
  // as \000 chars
  tty.c_iflag &= ~IGNBRK;         // disable break processing
  tty.c_lflag = 0;                // no signaling chars, no echo,
                                  // no canonical processing
  tty.c_oflag = 0;                // no remapping, no delays
  tty.c_cc[VMIN]  = 0;            // read doesn't block
  tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

  tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

  tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                  // enable reading
  tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
  tty.c_cflag |= parity;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CRTSCTS;

  if (tcsetattr (tty_file, TCSANOW, &tty) != 0)
  {
    Serial.printf("error %d from tcsetattr", errno);
    return -1;
  }
  return 0;
}

bool SerialClient::init(){
  tty_file = open(portname.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
  if(tty_file < 0)
  {
    return false;
  }

  set_interface_attribs(B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
  write(tty_file, "hello!\n", 7);           // send 7 character greeting
  usleep((7 + 25) * 100);             // sleep enough to transmit the 7 plus
                                       // receive 25:  approx 100 uS per char transmit
  Serial.printf("serial client connected\r\n");
  return true;
}

void SerialClient::loop(){
  if(serialInitialized){
    char buffer[100];
    ssize_t length = read(tty_file, &buffer, sizeof(buffer));
    if (length == -1)
    {
      //Error reading from serial port
      return;
    }
    else
    {
        buffer[length] = '\0';
        Serial.printf("%s", buffer);
    }
  }
  else{
    serialInitialized = init();
  }
}
