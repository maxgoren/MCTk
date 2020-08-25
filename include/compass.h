namespace mctk {
    class compass {
        public:
        std::array<Point, 8> dir;
        compass()
        {
             dir[0]={0,1}; dir[4]={1,1};        
             dir[1]={1,0}; dir[5]={1,-1};     
             dir[2]={0,-1}; dir[6]={-1,-1};     
             dir[3]={-1,0}; dir[7]={-1,1}; 
        }
    };
}