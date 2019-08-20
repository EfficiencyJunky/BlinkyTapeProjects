class Dot {
  Ring *r;
  public:
    int pos;
    float vel;
    float acc;
    CRGB color;
    void draw ();
    Dot(Ring *rr, CRGB c, int p, float v, float a) {
      color = c;
      pos = p;
      vel = v;
      acc = a;
      r = rr;
    }
    void updatePos();
};

void Dot::draw () {
  r->draw(pos, color);
}

void Dot::updatePos() {
  pos += vel;
  vel += acc;
  pos = pos % r->len;
  if (pos >= r->len) {
    pos -= r->len;
  } else if (pos < 0) {
    pos += r->len;
  }
}

