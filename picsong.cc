//
// this is bandclass2.cc (Band Class)
// a simple music maker program which is basically my retarded version of a software synthesizer
// taking concepts from the Yamaha SID chip's ADSR envelope generator
//
// copyright(c) 2008 by christopher abad
// aempirei@gmail.com
//
// g++ bandclass2.cc -Wall -lm -o bandclass2
//
// ./bandclass2 < filename.music > output.wav
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <map>

using namespace std;

struct ltstr {
   bool operator()(const char* s1, const char* s2) const {
      return strcmp(s1, s2) < 0;
   }
};

class note {

   // our duration is in 8th notes (a duration of 8 would be 1 whole note)
   // but tempo is in quarter notes per minute

   private:

   const static double key =  16.35; // this is the base key frequency of the instrument (16.35 is octave-0 C)

   map<const char *, int, ltstr> noteToNumber;

   public:

   static double calculateFrequency(int noteNumber, unsigned int octave) {
      if(noteNumber < 0)
         return 4;
      return key * pow(2, octave + (double)noteNumber / 12.0);
   }

   unsigned int tempo; // this is quarter notes per minute

   note() {
      noteToNumber["-"] = -1;
      noteToNumber["c"] = 0;
      noteToNumber["c#"] = 1;
      noteToNumber["db"] = 1;
      noteToNumber["d"] = 2;
      noteToNumber["d#"] = 3;
      noteToNumber["eb"] = 3;
      noteToNumber["e"] = 4;
      noteToNumber["f"] = 5;
      noteToNumber["f#"] = 6;
      noteToNumber["gb"] = 6;
      noteToNumber["g"] = 7;
      noteToNumber["g#"] = 8;
      noteToNumber["ab"] = 8;
      noteToNumber["a"] = 9;
      noteToNumber["a#"] = 10;
      noteToNumber["bb"] = 10;
      noteToNumber["b"] = 11;

      tempo = 60;
   }

   int getNoteNumber(const char *note) {

      map<const char *, int>::iterator iter = noteToNumber.find(note);
      assert(iter != noteToNumber.end() /* invalid note */);
      return noteToNumber[note];
   }
};

int
main(int argc, char **argv)
{
   note no;
   unsigned int tempo;
   int n;
   int i;

   if (argc != 1) {
      printf("\nusage: %s < music > output.s16le\n\n", *argv);
      exit(EXIT_FAILURE);
   }

   n = scanf("tempo = %u ", &tempo);
   assert(n == 1 && tempo > 0 /* tempo must be correctly set */);
   no.tempo = tempo;

   n = scanf("envelope = %*u %*u %*u %*u %*u %*u %*u %*u ");

   //
   // this is the main loop. read a note, generate it and repeat
   //

   n = scanf("music = ");

   i = 0;

   for(;;) {

      char note[8];
      unsigned int duration, octave;
      int noteNumber;
      int freq;

      if(feof(stdin))
         break;

      n = scanf("%u%4[aAbBcCdDeEfFgG#-]%u ", &duration, note, &octave);

      assert(n == 3);

      noteNumber = no.getNoteNumber(note);

      freq = (int)rint(note::calculateFrequency(noteNumber, octave - 1));

      // fprintf(stderr, "generated note %s (%i) duration %u octave %u (%i)\n", note, noteNumber, duration, octave, freq);

      printf("   note_fn .%i, GP4, .%i, .%i\n", i, freq, duration);

      i++;

   }

   exit(EXIT_SUCCESS);
}
