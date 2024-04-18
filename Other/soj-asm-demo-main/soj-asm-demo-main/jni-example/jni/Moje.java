public class Moje
{
  static native int celecislo( int neco );
  static native int pole( int arg[] );

  static 
  {
    System.loadLibrary("moje");
  }

  static public void main( String args[] )
  {
    int k[] = { 1, 2, 3, 4 , 5, 5, 5, 5, 5};
    System.out.println( "Vysledek je " + celecislo( 4 ) );
    System.out.println( "Delka pole je " + pole( k ) );
  }
}
