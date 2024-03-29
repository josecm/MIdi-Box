/************************
FILE_IO
*************************/

#include "FILE_IO.h"

FILE_IO::FILE_IO(string filename): MIDI_IO(), midiFile( (PATH_FILE + filename).data() ), midiFileName(filename), index(0)
{
    midiFile.absoluteTicks();
}

FILE_IO::~FILE_IO()
{

}

bool FILE_IO::open()
{
    midiFile.read(PATH_FILE + midiFileName);
    //if num tracks > 1 , join
    //if delta -> convert to absolute
    //order by tick
    //midiFile.absoluteTicks();

    return midiFile.status();
}

bool FILE_IO::close()
{
    midiFile.write(PATH_FILE + midiFileName);
    return midiFile.status();
}

void FILE_IO::truncate(){
    midiFile.clear();
}


void FILE_IO::setTicksPerQuarterNote(int tick){
    midiFile.setTicksPerQuarterNote(tick);
}

void FILE_IO::addMidiEvent(MidiEvent &event){
    midiFile.addEvent(event);
}

void FILE_IO::resetIndex(){
    index = 0;
}


int FILE_IO::getNextMidiMsg(int channel, int tick)
{
    MidiEvent event;

    while((event = midiFile.getEvent(0, index)).tick == tick){

        //if() continue; //cases to ignore
        printf("0\n");
        MidiMessage msg;
        msg.setSize(event.getSize());

        for(int i=0; i < event.getSize(); i++){
            msg[i] = event[i];
        }

        writeInMidiMsg(channel, msg);
        index++;

        if (index == midiFile.getNumEvents(0)){
            resetIndex();
            return 0;
        }

    }

    return 1;
}
