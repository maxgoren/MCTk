//How it works:  automaton()->prep_fields()->place_seeds()->four_five()->flood_fill()->automaton() -> done.
//                                                            v   ^ 
//                                                      count_neighbors()
//How its used: Cave myCave(160, 40);
//              myCave.automaton();
//
//The completed cave is then available as myCave.layout;


//need this hash to be able to use Point with std::unordered_map.
//which is used during the flood_fill stage.


namespace mctk {

struct hashZ {
  std::size_t operator()(const Point pt) const {
      std::size_t x = std::hash<int>()(pt.x);
      std::size_t y = std::hash<int>()(pt.y >> 4);
    return x^y;
  }
};


//easier than typing out -v- that a bunch of times.
typedef std::vector<std::vector<Point>> field;



class Cave {
    private:
        int mapW;
        int mapH;
        std::array<Point, 8> cdir;
        field layout;
        field temp;
        bool hasmaze;
        void prep_fields();
        int count_neightbors(Point p, field working);
        field flood_fill(field working);
        field place_seed(field seed);
        field four_five(field working);
    public:
    zone getZone();
    void make_cave();
    Cave(zone outline);
};

}