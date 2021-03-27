package proj.musicxml.note;

public interface NoteType
{
  
  public Chord getChord();
  
  public NotePitchType getNotePitchType();
  
  public Duration getDuration();
  
  public void setDuration(Duration duration);

}
