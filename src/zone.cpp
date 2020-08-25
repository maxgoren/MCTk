namespace mctk {

    Point mctk::zone::getSpawn()
    {
        Point ret;
        if (openSpace.size() > 0)
        {
            ret = openSpace.at(getrand(3, openSpace.size() - 1));
            std::cout<<"Spawning: "<<ret.x<<"/"<<ret.y<<"\n";
        } else {
            ret = {mapW/2,mapH/2};
        }
        return ret;
    }
}