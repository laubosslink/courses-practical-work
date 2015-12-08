#ifndef IMAGEENSEMBLE_H
#define IMAGEENSEMBLE_H

template <typename T> T operator*(Ensemble<T> & e) {
  return Ensemble<T>::iterator(e).getCurrent();
}

template <typename T> class Function {
public:
  virtual T operator()(T x)=0;
};

template <typename T> class Affine : public Function<T> {
private:
  int a, b;
public:
  Affine(int a, int b): a(a), b(b){}
  T operator()(T x){
    return a*x + b;
  }
};

/* @todo replace Affine par Function */
template <typename T> Ensemble<T> imageEnsemble(Affine<T> function, Ensemble<T> & e)
{
  Ensemble<double>::iterator it(e); /* @todo remplacer <double< par <T> */
  Ensemble<T> i;

  //if(it.getCurrent() != nullptr) // @todo verifier qu'il y ait un premier element
    i.ajoute(function(it.getCurrent()));

  while(it.hasNext())
  {
    it.next();
    i.ajoute(function(it.getCurrent()));
  }

    return i;
}

#endif
