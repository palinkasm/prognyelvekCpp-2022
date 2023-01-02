// A Pipe osztály a Unix pipe-ok működését szimulálja. Sablon paramétere a
// csővezetéken végighaladó adat tí­pusát határozza meg. add_operation()-nel
// lehessen függvényt hozzáadni a pipe-hoz. run()-nal hajtsuk végre az összes
// hozzáadott függényt sorban: első függvény a kiinduló adatot kapja meg,
// második függvény az első eredményét,... N. függvény az N-1. eredményét.
// Ha a pipe üres, azaz nincs benne művelet, akkor a végrehajtás az eredeti adatot adja vissza.
// A clear() szedje ki az összes műveletet a pipe-ból.
// Tudjunk Pipe-ot konstruálni egy függvényből implicit.
// A Pipe objektumot lehessen függvényként is futtatni.
// A += operátor fűzze hozzá a baloldali pipe végére a jobboldali műveleteit.
// Ha két Pipe közé | operátort í­runk, akkor az gyártsa le a két Pipe összekapcsolását.

#include <iostream>
#include "pipe.h"
#include <algorithm>
#include "pipe.h"
#include <sstream>

int triple( int x ) { return 3 * x; }

int invert_sign( int x ) { return -1 * x; }

int inc( int x ) { return x + 1; }

int dec( int x ) { return x - 1; }

std::string tolower_firstchar( std::string s )
{
  s[0] = (char)std::tolower((unsigned char)s[0]);
  return s;
}

std::string first_half( std::string s ) { return s.substr(0, s.length() / 2); }

std::string prefix_with_length( std::string s )
{
  std::stringstream ss;
  ss << s.length() << ":" << s;
  return ss.str();
}

std::string duplicate( std::string s ) { return s + s; }

bool check()
{
  Pipe<int> p;
  p.add_operation( inc );
  p.add_operation( triple );
  p.add_operation( invert_sign );
  p.add_operation( dec );

  Pipe<std::string> q;
  q.add_operation( tolower_firstchar );
  q.add_operation( first_half );

  if ( p.run( 10 ) != -34 || p( 4 ) != -16 ||
       q.run( "Hello world!" ) != "hello " )
  {
    return false;
  }

  q += q;

  Pipe<std::string> r;
  r.add_operation( tolower_firstchar );
  r.add_operation( prefix_with_length );
  std::vector<std::string> v;
  v.push_back( "C++" );
  v.push_back( "Python" );
  v.push_back( "Haskell" );
  std::transform( v.begin(), v.end(), v.begin(), r );

  if ( q( "Hello world!" ) != "hel" ||
       v[ 0 ] != "3:c++" || v[ 1 ] != "6:python" || v[ 2 ] != "7:haskell" )
  {
    return false;
  }

  Pipe<std::string> s = duplicate;
  s += s;

  Pipe<int> t = Pipe<int>( inc ) | inc | triple | invert_sign;

  if ( s.run( "Hello" ) != "HelloHelloHelloHello" || t( 4 ) != -18 ||
       (q | r | s)( "ABCDEFGH" ) != "2:aB2:aB2:aB2:aB" )
  {
    return false;
  }

  return true;
}

int main()
{
  std::cout
    << "Your solution is " 
    << (check() ? "" : "not ")
    << "ready for submission."
    << std::endl;
}