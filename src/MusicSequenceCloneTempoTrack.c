/*!
 @header MusicSequenceCloneTempoTrack.c
 @abstract   <#abstract#>
 @discussion <#description#>
 */
#include <AudioToolbox/MusicPlayer.h>

/*!
    @function
    @abstract   Clone tempo track from sequence to sequence
    @discussion Destination sequence must be empty. Remove  default event from destination at timestamp 0.
    @param      <#(name) (description)#>
    @result     <#(description)#>
 	@copyright	Andrea Tassotti
*/
OSStatus MusicSequenceCloneTempoTrack(MusicSequence inSequence, MusicSequence outSequence)
{
	OSStatus err;
	MusicTrack inTempoTrack, outTempoTrack;
	MusicTimeStamp inSourceEndTime;
	UInt32 propsize = sizeof(MusicTimeStamp);
	UInt32 ntracks;
	
	

	err = MusicSequenceGetTrackCount (outSequence, &ntracks);
	if ( err != noErr)
	{
		fprintf(stderr, "MusicSequenceGetTrackCount got error %i for inSequence\n", err);
		return err;
	}

	// outSequence must be empty
	if ( ntracks > 0)
	{
		fprintf(stderr, "MusicSequenceCloneTempoTrack: destination must be empty\n");
		return -50;
	}
	
	err =  MusicSequenceGetTempoTrack ( outSequence, &outTempoTrack );
	if ( err != noErr)
	{
		fprintf(stderr, "MusicSequenceGetTempoTrack got error %i for outSequence\n", err);
		return err;
	}
	err =  MusicSequenceGetTempoTrack ( inSequence, &inTempoTrack );
	if ( err != noErr)
	{
		fprintf(stderr, "MusicSequenceGetTempoTrack got error %i for inSequence\n", err);
		return err;
	}

	err = MusicTrackGetProperty(inTempoTrack, kSequenceTrackProperty_TrackLength,
								&inSourceEndTime, &propsize);
	if ( err != noErr )
	{
		fprintf(stderr, "MusicTrackGetProperty got error %i\n", err);
		return err;
	}
	

	// Remove Time event in destination
	MusicEventIterator iterator;
	err = NewMusicEventIterator(outTempoTrack, &iterator);
	if ( err != noErr )
	{
		fprintf(stderr, "NewMusicEventIterator got error %i\n", err);
		return err;
	}

	Boolean hasCurrentEvent;
	
	err = MusicEventIteratorHasCurrentEvent (iterator, &hasCurrentEvent);
	if ( err != noErr )
	{
		fprintf(stderr, "MusicEventIteratorHasCurrentEvent got error %i\n", err);
		return err;
	}	

	while (hasCurrentEvent) {
		err = MusicEventIteratorDeleteEvent(iterator);
		err = MusicEventIteratorHasCurrentEvent (iterator, &hasCurrentEvent);
	}
	
	err = DisposeMusicEventIterator(iterator);

	// Do the copy
	// Extra time at the end for get all events
	err = MusicTrackCopyInsert (inTempoTrack, 0, 1.0 + inSourceEndTime, outTempoTrack, 0 );
	
	return err; 
}

