// -*- C++ -*-
//
// $Id: t_foo.cc,v 1.33 2004-03-22 11:08:33 bjoo Exp $
//
/*! \file
 *  \brief Silly little internal test code
 */


#include "qdp.h"
#include "qdp_iogauge.h"

//using namespace std;

using namespace QDP;

struct Nearest : public MapFunc
{
  Nearest() {}

  virtual multi1d<int> operator() (const multi1d<int>& coord, int sign) const
    {
      multi1d<int> lc = coord;

      const multi1d<int>& nrow = Layout::lattSize();
      int m = 1;
      lc[m] = (coord[m] + 1*sgnum(sign) + 4*nrow[m]) % nrow[m];

      return lc;
    }

private:
  int sgnum(int x) const {return (x > 0) ? 1 : -1;}
}; 


struct NearestNeighborMapFunc : public ArrayMapFunc
{
  NearestNeighborMapFunc() {}

  virtual multi1d<int> operator() (const multi1d<int>& coord, int sign, int dir) const
    {
      multi1d<int> lc = coord;

      const multi1d<int>& nrow = Layout::lattSize();
      lc[dir] = (coord[dir] + sgnum(sign) + 4*nrow[dir]) % nrow[dir];

      return lc;
    }

  virtual int numArray() const {return Nd;}

private:
  int sgnum(int x) const {return (x > 0) ? 1 : -1;}
}; 



int main(int argc, char *argv[])
{
  // Put the machine into a known state
  QDP_initialize(&argc, &argv);

  // Setup the layout
  const int foo[] = {2,2,2,2};
  multi1d<int> nrow(Nd);
  nrow = foo;  // Use only Nd elements
  Layout::setLattSize(nrow);
  Layout::create();

  NmlWriter nml("foo.nml");
//  nml.open("foo.nml");

  write(nml,"nrow", nrow);
#if defined(ARCH_PARSCALAR)
  write(nml,"logicalSize",Layout::logicalSize());
#endif

#if 1
  LatticeFermion foo
#if 0
  QDPIO::cerr << "Open t_foo.input" << endl;

  NmlReader nml_in("t_foo.input");
  {
    int x;
    push(nml_in,"stuff");
    read(nml_in,"x", x);  
    write(nml,"x", x);
  }
  nml_in.close();
#endif

#if 0
  {
    LatticeFermion a,b;
    random(a); random(b);
    Double   rfoo;
    DComplex foo;
    rfoo = norm2(a);
    foo = innerProduct(a,b);
    write(nml,"rfoo", rfoo);
  }
#endif

#if 0
  {
    LatticeColorMatrix a,b,c;
    a = b = c = 1;

    LatticeComplex e;
    e = colorContract(a,b,c);

    write(nml,"e",e);
  }
#endif
  
#if 0
  {
    LatticeColorVector a,b,c;
    LatticeReal one = 1;
    LatticeComplex comp = cmplx(one,0);

    // Setting a,b,c = 1 for all components should cancel after contraction
    c = zero;
    for(int m=0; m < Nc; ++m)
      pokeColor(c,comp,m);

    a = b = c;
    LatticeComplex f;
    f = colorContract(a,b,c);

    write(nml,"f", f);

    // Setting a,b,c = 1 for just 1 set of components should not cancel
    a = b = c = zero;
    pokeColor(a,comp,0);
    pokeColor(b,comp,2);
    pokeColor(c,comp,1);

    LatticeComplex g;
    g = colorContract(a,b,c);

    write(nml,"g", g);
  }
#endif
  
#if 0
  {
    Map near;
    Nearest bbb;
    near.make(bbb);

    LatticeReal fred,sue;
    random(fred);

    sue = near(fred);

    write(nml,"fred", fred);
    write(nml,"sue", sue);
  }
#endif

#if 0
  {
    BiDirectionalMap near;
    Nearest bbb;
    near.make(bbb);

    LatticeReal fred,sue,sam;
    random(fred);

    sue = near(fred,+1);
    sam = near(fred,-1);

    write(nml,"fred", fred);
    write(nml,"sue", sue);
    write(nml,"sam", sam);
  }
#endif

#if 0
  {
    ArrayMap nearneigh;
    NearestNeighborMapFunc bbb;
    nearneigh.make(bbb);

    LatticeReal fred,sue;
    random(fred);

    write(nml,"fred", fred);
    for(int m=0; m < Nd; ++m)
    {
      sue = nearneigh(fred,m);
      write(nml,"m", m);
      write(nml,"sue", sue);
    }
  }
#endif

#if 0
  {
    ArrayBiDirectionalMap nearneigh;
    NearestNeighborMapFunc bbb;
    nearneigh.make(bbb);

//    LatticeReal fred,sue,sam;
    LatticeColorMatrix fred;
    random(fred);

    write(nml,"fred", fred);
    for(int m=0; m < Nd; ++m)
    {
      LatticeColorMatrix sue = nearneigh(fred,+1,m);
      LatticeColorMatrix sam;
      sam = nearneigh(fred,-1,m);

      write(nml,"m", m);
      write(nml,"sue", sue);
      write(nml,"sam", sam);
    }
  }
#endif

//  exit(0);

  QDPIO::cerr << "try a string\n";
  nml << "write a string";

  Real one = 1.0;
  QDPIO::cerr << "try a scalar\n";
  nml << "write a scalar";
  write(nml,"test this",one);
//  exit(0);

  QDPIO::cerr << "latticereal\n";
  LatticeReal bar = 17.0;
  random(bar);

//  for(int i=0; i < Layout::subgridVol(); ++i)
//    QDPIO::cerr << "bar[" << i << "]=" << bar.elem(i) << endl;

  QDPIO::cerr << "write\n";
  write(nml,"bar", bar);
  QDPIO::cerr << "done write\n";

#if 0
  // Initialize the random number generator
  Seed seed;
  seed = 11;
  nml << seed;
  RNG::setrn(seed);
#endif


//  typedef QDPType<int> LatticeInteger;
//  typedef OLattice<int> LatticeInteger;
//  typedef QDPType<OLattice<int> > LatticeInteger;
//  LatticeComplexInteger a, b, c;
//  LatticeReal a, b, c;
  LatticeReal a, b, c, e;
  Complex d;
//  float ccc = 2.0;
//  float x;
  
#if 0
  LatticeComplex  foob(zero);
  nml << "Here is foob";
  write(nml,"foob", foob);
#endif


#if 0
  b = 3;
  c = 4;
  d = 5;

  b[rb[1]] = zero;

  nml << "First set of b";
  write(nml,"b", b);

  random(b);

  nml << "Second set of b";
  write(nml,"b", b);

  b[rb[0]] = -17;

  nml << "Third set of b";
  write(nml,"b", b);

//  b.elem(1).elem() = -1;
//  b.elem().elem(1).elem() = -1;
//  b.elem().elem(1) = -1;

  nml << "here 0";
#endif
//  a = -b + c*d;
//  a = c*d - b;
//  a = b*c;
//  a = -b + ccc*c;
//  a = -b + 2*c;
  a = shift(b*c,FORWARD,0);
//  a = b*c;
//  a = ccc*c;
//  x = ccc*c;

  nml << "here b";
  write(nml,"b", b);
  nml << "here a";
  write(nml,"a",a);

  nml << "here e";
  LatticeReal rr;
//  random(rr);
  rr = 0.2;
  e = where(rr < 0.5, a, c);
  write(nml,"e",e);


#if 0
  nml << "test peekColor";
  LatticeColorMatrix barf = 1.0;
  LatticeComplex fred = peekColor(barf,0,0);
  write(nml,"barf", barf);
  write(nml,"fred", fred);

  multi1d<int> ccrd(Nd);
  ccrd = 1;

  nml << "test peeksite";
  random(fred);
  Complex sitefred = peekSite(fred,ccrd);
  write(nml,"fred", fred);
  write(nml,"sitefred", sitefred);


  nml << "test pokeColor";
  random(barf);
  fred = 1.0;
  LatticeColorMatrix barfagain = pokeColor(barf,fred,0,0);
  write(nml,"barfagain", barfagain);

  nml << "test pokeSite";
  random(sitefred);
  LatticeComplex fredagain = pokeSite(fred,sitefred,ccrd);
  write(nml,"fredagain", fredagain);
#endif


#if 0

  a = -b + ccc*c;
//  a = ccc*c;

  nml << "here a";
  write(nml,"a", a);
#endif

#if 0
//  std::ofstream f;
//  f.open("foobar",std::ios_base::out|std::ios_base::binary);
//  float aa[3] = {0.0,0.0,0.0};
//  std::fwrite(&aa,sizeof(LatticeComplex),1,f.rdbuf());
//  f.close();


  {
    NmlWriter to("fred.txt");
    write(to,"a",a);
  }

  {
    QDPIO::cerr << "open fred.bin\n";
    BinaryWriter to("fred.bin");
    write(to,a);
  }

  {
    float x;
    QDPIO::cerr << "enter some data" << endl;
    TextReader from("input");
    from >> x;

    QDPIO::cerr << "float: you entered :" << x << ":" << endl;
  }

  {
    Real x;
    QDPIO::cerr << "enter some data" << endl;
    TextReader from("input");
    from >> x;

    QDPIO::cerr << "Real: you entered :" << x << ":" << endl;
  }

  
  // Zero out a and read it again
  a = zero;

  {
    BinaryReader from("fred.bin");
    read(from,a);
  }

  nml << "Reset and reread a";
  write(nml,"a",a);

#endif

#if 0
 {
   QDPIO::cerr << "create metadata xml" << endl;

   XMLBufferWriter xml;

   push(xml,"fred");
   float yy = 42.1;
   write(xml,"yy",yy);
   Real zzz = 3.1;
   Complex zz = cmplx(17.5,zzz);
   write(xml,"zz",zz);

#if 0
   LatticeComplex ee;
   random(ee);
   write(xml,"ee",ee);

   LatticeFermion ff;
   random(ff);
   write(xml,"ff",ff);
#endif

   pop(xml);

   QDPIO::cout << "Here is the metadata" << endl << xml.str() << endl;

   XMLFileWriter file_xml("t_foo.xml_output");
   file_xml.writeXML(xml.printRoot());
 }
#endif

#if 0
 {
   QDPIO::cerr << "read metadata xml" << endl;

   XMLReader xml;
   xml.open("t_foo.xml_output");

   float yy;
   read(xml,"/fred/yy",yy);
   write(nml,"yy", yy);

   QDPIO::cerr << "Found reading metadata xml that  yy = " << yy << endl;

//   Complex zz;
//   read(xml,"zz",zz);
//   write(nml,"zz",zz);
 }
#endif

#if 0
 {
   QDPIO::cerr << "create xml" << endl;

   XMLBufferWriter file_xml;
   string file_string = "Here is the file xml";
//   int file_string = -1;
   push(file_xml,"foo");
   write(file_xml,"file_string",file_string);
   pop(file_xml);

   XMLBufferWriter rec_xml;
   string rec_string = "Here is the record xml";
//   int rec_string = -3;
   push(rec_xml,"boo");
   write(rec_xml,"rec_string",rec_string);
   pop(rec_xml);

   gaussian(a);
   gaussian(b);
   nml << "Test of QDPSerialFileWriter - here first is a";
   write(nml,"a",a);
   nml << "Test of QDPSerialFileWriter - here first is a";
   write(nml,"b", b);

   QDPIO::cerr << "create serialwriter" << endl;
   QDPSerialFileWriter to(file_xml,"fred.dime");
   QDPIO::cerr << "write to" << endl;
   to.write(rec_xml,a);
   QDPIO::cerr << "end write" << endl;
   to.write(rec_xml,b);
   QDPIO::cerr << "end write" << endl;
   to.close();

   nml << "Test of QDPSerialFileWriter";
   write(nml,"a",a);
   write(nml,"b",b);
 }
#endif

#if 0
 {
   QDPIO::cerr << "create xml" << endl;

   XMLReader file_xml;
   XMLReader rec_xml;

   a = 0;
   b = 0;

   QDPIO::cerr << "open serialreader" << endl;
   QDPSerialFileReader from(file_xml,"fred.dime");
   QDPIO::cerr << "read from file" << endl;
   from.read(rec_xml,a);
   QDPIO::cerr << "end read 1" << endl;
   from.read(rec_xml,b);
   QDPIO::cerr << "end read 2" << endl;

   nml << "Read a and b from QDPSerialFileReader";
   write(nml,"a", a);
   write(nml,"b", b);
 }
#endif

#if 1
  if (Nd == 4)
  {
    // Read a nersc file
    multi1d<LatticeColorMatrix> u(Nd);
    readArchiv(u, "archiv.cfg");
    nml << "Here is the nersc archive u field";
    write(nml,"u",u);
  }
#endif


#if 0
  if (Nd == 4)
  {
    // Read a szin gauge file
    multi1d<LatticeColorMatrix> u(Nd);
    Seed seed_old;
    QDPIO::cerr << "Calling szin reader" << endl;
    readSzin(u, 0, "szin.cfg", seed_old);
    nml << "Here is the SZIN u field";
    write(nml,"u", u);
  }
#endif


#if 0
  if (Nd == 4)
  {
    // Read a szin quark prop file
    LatticePropagator qprop;
    QDPIO::cerr << "Read a szin qprop" << endl;
    readSzinQprop(qprop, "propagator_0");
    nml << "Here is the szin quark prop";
    write(nml,"qprop", qprop);
  }
#endif


#if 0
  LatticeInteger d;
  nml << "here c";
  const Expression<BinaryNode<OpAdd,
    Reference<LatticeInteger>, Reference<LatticeInteger> > > &expr1 = b + c;
  nml << "here d";
  d = expr1;
  nml << "here e";
  nml << d;
  nml << "here f";
  
  int num = forEach(expr1, CountLeaf(), SumCombine());
  nml << num << endl;

//  const Expression<BinaryNode<OpAdd, Reference<LatticeInteger>, 
//    BinaryNode<OpMultiply, Scalar<int>,
//    Reference<LatticeInteger> > > > &expr2 = b + 3 * c;
//  num = forEach(expr2, CountLeaf(), SumCombine());
//  nml << num << endl;
  
  const Expression<BinaryNode<OpAdd, Reference<LatticeInteger>, 
    BinaryNode<OpMultiply, Reference<LatticeInteger>,
    Reference<LatticeInteger> > > > &expr3 = b + c * d;
  num = forEach(expr3, CountLeaf(), SumCombine());
  nml << num << endl;
#endif

  // Time to bolt
  QDP_finalize();

  exit(0);
}
