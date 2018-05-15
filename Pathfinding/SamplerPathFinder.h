//
//  SamplerPathFinder.h
//  testGlut
//
//  Created by Vivek Seetharaman on 4/4/13.
//  Copyright 2013 Sourcebits Technologies. All rights reserved.
//

#ifndef testGlut_SamplerPathFinder_h
#define testGlut_SamplerPathFinder_h


#include<vector>
using namespace std;

/*
 *  This class is used to visualize the search progression. The PathFinder will update this class every frame with processing details of that frame.
    This class in tern will be used by an external visualizer like a tilemap renderer to display the search progression every frame
 */
class SamplerPathFinder
{
public:
    vector<int> m_NodesVisitedThisFrame;
};

#endif
