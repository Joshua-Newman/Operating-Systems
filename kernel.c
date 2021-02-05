/* LAB4 version */
/* ACADEMIC INTEGRITY PLEDGE                                              */
/*                                                                        */
/* - I have not used source code obtained from another student nor        */
/*   any other unauthorized source, either modified or unmodified.        */
/*                                                                        */
/* - All source code and documentation used in my program is either       */
/*   my original work or was derived by me from the source code           */
/*   published in the textbook for this course or presented in            */
/*   class.                                                               */
/*                                                                        */
/* - I have not discussed coding details about this project with          */
/*   anyone other than my instructor. I understand that I may discuss     */
/*   the concepts of this program with other students and that another    */
/*   student may help me debug my program so long as neither of us        */
/*   writes anything during the discussion or modifies any computer       */
/*   file during the discussion.                                          */
/*                                                                        */
/* - I have violated neither the spirit nor letter of these restrictions. */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Signed:_Andrew Weaver && Joshua Newman  Date: February 28, 2020        */
/*                                                                        */
/*                                                                        */
/* 3460:4/526 BlackDOS2020 kernel, Version 1.03, Spring 2020              */

/*                                                                        */
/* Declare functions                                                      */
/*                                                                        */

void handleInterrupt21(int,int,int,int);
void handleInterrupt33(int,int,int,int);
void printLogo();
void clearScreen(int, int);
void readString(char* c);
void printString(char*, int);
void readInt(int*);
void writeInt(int, int);
void readSector(char*, int, int);
void writeSector(char*, int, int);
void runProgram(int, int, int);
void stop();
int mod(int, int);
int div(int, int);

void main()
{
   char buffer[512];
   int i;

   makeInterrupt21();

   /* initialize buffer */
   for (i=0; i < 512; i++)
      buffer[i]=0;

   /* read configuration file at sector 258 */
   interrupt(33, 2, buffer, 258, 1);

   /* clear screen with new color scheme */
   interrupt(33, 12, buffer[0]+1, buffer[1]+1, 0);

   printLogo();

   /* run selected program */
   runProgram(30,4,2);
   interrupt(33, 0, "Error if this executes. \r\n\0", 0, 0);

}

void printString(char* c, int d)
{
   char al;
   char ah = 14;   /* function 14 call */
   int i = 0;      /* string index */
   int ax;
   int interruptDisplay = 16; /* interrupt number 16 for outputting to display */
   int interruptPrint = 23; /* interrupt number 23 for outputting to printer */

   /* if/else to determine path of char string */
   if(d)
   {
     /* interrupt for outputting to the printer..*/
     while(c[i] != '\0')
     {
         al = c[i];
         interrupt(interruptPrint, al, 0, 0, 0);
         i++;
      }
     return;
   }
   else
   {
     /* interrupt for printing output to screen*/
     while(c[i] != '\0') {
         al = c[i];
         ax = ah * 256 + al;
         interrupt(interruptDisplay, ax, 0, 0, 0);
         i++;
     }
     return;
 }
}

void printLogo()
{
   printString("       ___   `._   ____  _            _    _____   ____   _____ \r\n\0",0);
   printString("      /   \\__/__> |  _ \\| |          | |  |  __ \\ / __ \\ / ____|\r\n\0",0);
   printString("     /_  \\  _/    | |_) | | __ _  ___| | _| |  | | |  | | (___ \r\n\0",0);
   printString("    // \\ /./      |  _ <| |/ _` |/ __| |/ / |  | | |  | |\\___ \\ \r\n\0",0);
   printString("   //   \\\\        | |_) | | (_| | (__|   <| |__| | |__| |____) |\r\n\0",0);
   printString("._/'     `\\.      |____/|_|\\__,_|\\___|_|\\_\\_____/ \\____/|_____/\r\n\0",0);
   printString(" BlackDOS2020 v. 1.03, c. 2019. Based on a project by M. Black. \r\n\0",0);
   printString(" Author(s): Josh Newman and Andy Weaver\r\n\r\n\0",0);
}

void clearScreen(int bx, int cx)
{
  int interruptClear = 16;
  int i; /* loop index */
  int AX, DX;

  for (i = 0; i < 24; ++i)
  {
    /* 24 carriage returns with \r */
    interrupt(interruptClear, 14*256 + '\r', 0, 0, 0);
    /* 24 newlines with \n */
    interrupt(interruptClear, 14*256 + '\n', 0, 0, 0);
  }

  /* reposition cursor in upper left-hand corner - (0,0) */
  interrupt(interruptClear, 512, 0, 0, 0);

  /* */
  if ((bx > 0) && (cx > 0))
    interrupt(interruptClear, 1536, 4096 * (bx-1) + 256 * (cx-1), 0, 6223);

}

void readString(char* c)
{
  int interruptDisplay = 16;
  int interruptCharacter = 22;
  int i = 0;
  char* in;

  do{
    in = interrupt(interruptCharacter,0,0,0,0); /*read in character*/

    if(in==13)
    {
      interrupt(interruptDisplay, 3584+10, 0, 0, 0);  /* newline*/
      interrupt(interruptDisplay, 3584+in, 0, 0, 0);  /*Carriage Return*/
      break;
    }
    if(in==8)
    {			/* backspace pressed*/
      interrupt(interruptDisplay, 3584+in, 0, 0, 0);  /* delete character */
      interrupt(interruptDisplay, 3584+32, 0, 0, 0);  /* overwrite with space*/
      interrupt(interruptDisplay, 3584+in, 0, 0, 0);  /* delete space*/
      if(i>0)
      {
       i--;				/*step back iter -- originally '--i' */
      }
    }
    else
    {
      interrupt(interruptDisplay,3584+in,0,0,0);    /*display character*/
      c[i]=in;
      i++;              /*next character location -- originally '++i' */
    }
  } while(1); 		/*enter pressed*/
  c[i]=0x0;		/*add null terminator*/
  return;
}


void readInt(int* k)
{
  int num = 0;
  int i=0;
  char intString[6]; /* 5 digits and a null terminator */

  interrupt(33,1,intString,0,0);
  while(intString[i]!='\0')
  {
    num *= 10;
    num += (intString[i++]-'0');
  }
  *k = num;
  return;
}

void writeInt(int num, int d)
{
  int i=0;
  int j=0;
  char intString[6]; /*held 5 integers and a null terminator */
  char revString[6]; /*held 5 integers and a null terminator */

  /* handle the zero case */
  if (!num)
  {
    intString[0]='0';
    intString[1]='\0';				//if 0, print 0
  }

  /* handle the general case */
  else
  {
    while (num)
    {
      revString[i++]=(char)(mod(num,10)+'0');  /*stores Least Sig Digit */
      num=div(num,10);                         /*updates LSD */
    } 				 /*stores number in reverse order */

    while(i-- > 0)
    {
      intString[j++]=revString[i]; /* reverse the revString */
    }
    intString[j]='\0';
  }
  interrupt(33,0,intString,d,0);   /* print number */
  return;
}


int mod(int a, int b)
{
  int quotient = div(a,b);
  int remainder = a - (quotient * b);
  return;
}

int div(int a, int b)
{
  int q = 0;

  while ((q * b) <= a)
    q++;
  return (q-1);
}


void readSector(char* buffer, int sector, int sectorCount)
{
  int readFlag = 2;
  int interruptSector = 19;
  int deviceNo = 0;              /* floppy disk device */
  int AX, BX, CX, DX;
  int relSecNo, headNo, trackNo;

  /* absolute to relative sector conversions */
  relSecNo = mod(sector, 18) + 1;
  headNo = mod(div(sector, 18), 2);
  trackNo = div(sector, 36);

  AX = readFlag * 256 + sectorCount;
  CX = trackNo * 256 + relSecNo;
  DX = headNo * 256 + deviceNo;

  /* issue the full readSector instruction */
  interrupt(interruptSector, AX, buffer, CX, DX);

  return;
}


void writeSector(char* buffer, int sector, int sectorCount)
{
  int writeFlag = 3;
  int interruptSector = 19;
  int deviceNo = 0;              /* floppy disk device */
  int AX, BX, CX, DX;
  int relSecNo, headNo, trackNo;

  /* absolute to relative sector conversions */
  relSecNo = mod(sector, 18) + 1;
  headNo = mod(div(sector, 18), 2);
  trackNo = div(sector, 36);

  AX = writeFlag * 256 + sectorCount;
  CX = trackNo * 256 + relSecNo;
  DX = headNo * 256 + deviceNo;

  /* issue the full writeSector instruction */
  interrupt(interruptSector, AX, buffer, CX, DX);

  return;
}

void runProgram(int start, int size, int segment)
{
  int i;
  int segmentLocation;
  char buffer[13312];                // Big char array

  readSector(buffer,start,size);     // store sectors into buffer
  segmentLocation = segment * 4096;  // segment * 0x1000 = base location of seg

  for (i = 0; i < 13311; ++i)        //xfer 13312 bytes to memory
  {
    //transfer byte i from buffer to memory
    putInMemory(segmentLocation, i, buffer[i]);
  }

  /* call the launchProgram to run in BOCHS */
  launchProgram(segmentLocation);
}

void stop()
{
  while(1);
}


void handleInterrupt21(int ax, int bx, int cx, int dx)
{
  switch(ax)
   {
      case 0:
        printString(bx, cx);
        break;
      case 1:
        readString(bx);
        break;
      case 2:
        readSector(bx, cx, dx);
        break;
      case 5:
        stop();
        break;
      case 6:
	writeSector(bx, cx, dx);
	break;
      case 12:
	clearScreen(bx, cx);
      case 13:
        writeInt(bx, cx);
        break;
      case 14:
        readInt(bx);
        break;
/*      case 3: case 4: case 7: case 8: case 9: case 10: */
/*      case 11: */
      default: printString("General BlackDOS error.\r\n\0",0);
   }
}
