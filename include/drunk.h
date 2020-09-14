class landscape {
    public:
    int mapW;
    int mapH;

    Helpers aux;
    bool onmap(Point p);
    field biased_walk(field layout, float percent_clear);
    field bounding_walk(field layout);
    field play(field layout);
    field make_it(field layout, int mapW, int mapH);
    landscape();
};