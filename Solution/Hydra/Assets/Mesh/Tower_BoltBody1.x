xof 0303txt 0032


template VertexDuplicationIndices { 
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}
template XSkinMeshHeader {
 <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
 WORD nMaxSkinWeightsPerVertex;
 WORD nMaxSkinWeightsPerFace;
 WORD nBones;
}
template SkinWeights {
 <6f0d123b-bad2-4167-a0d0-80224f25fabb>
 STRING transformNodeName;
 DWORD nWeights;
 array DWORD vertexIndices[nWeights];
 array float weights[nWeights];
 Matrix4x4 matrixOffset;
}

Frame RootFrame {

  FrameTransformMatrix {
    1.000000,0.000000,0.000000,0.000000,
    0.000000,-0.000000,1.000000,0.000000,
    0.000000,1.000000,0.000000,0.000000,
    0.000000,0.000000,0.000000,1.000000;;
  }
Frame Cube_017 {

  FrameTransformMatrix {
    1.000000,0.000000,0.000000,0.000000,
    0.000000,1.000000,0.000000,0.000000,
    0.000000,0.000000,1.000000,0.000000,
    0.000000,0.000000,0.000000,1.000000;;
  }
Mesh {
156;
1.000000; 1.000000; -0.001200;,
1.000000; -1.000000; -0.001200;,
-1.000000; -1.000000; -0.001200;,
-1.000000; 1.000000; -0.001200;,
1.000000; 1.000000; 0.100500;,
-1.000000; 1.000000; 0.100500;,
-1.000000; -1.000000; 0.100500;,
1.000000; -1.000000; 0.100500;,
1.000000; 1.000000; -0.001200;,
1.000000; 1.000000; 0.100500;,
1.000000; -1.000000; 0.100500;,
1.000000; -1.000000; -0.001200;,
1.000000; -1.000000; -0.001200;,
1.000000; -1.000000; 0.100500;,
-1.000000; -1.000000; 0.100500;,
-1.000000; -1.000000; -0.001200;,
-1.000000; -1.000000; -0.001200;,
-1.000000; -1.000000; 0.100500;,
-1.000000; 1.000000; 0.100500;,
-1.000000; 1.000000; -0.001200;,
1.000000; 1.000000; 0.100500;,
1.000000; 1.000000; -0.001200;,
-1.000000; 1.000000; -0.001200;,
-1.000000; 1.000000; 0.100500;,
0.000700; -0.020600; 0.088000;,
0.341200; 0.569100; 0.088000;,
0.681700; -0.020600; 0.088000;,
0.000700; -0.020600; 0.088000;,
0.681700; -0.020600; 0.088000;,
0.341200; -0.610300; 0.088000;,
0.000700; -0.020600; 0.088000;,
0.341200; -0.610300; 0.088000;,
-0.339800; -0.610300; 0.088000;,
0.000700; -0.020600; 0.088000;,
-0.339800; -0.610300; 0.088000;,
-0.680200; -0.020600; 0.088000;,
0.000700; -0.020600; 0.088000;,
-0.680200; -0.020600; 0.088000;,
-0.339800; 0.569100; 0.088000;,
0.000700; -0.020600; 0.088000;,
-0.339800; 0.569100; 0.088000;,
0.341200; 0.569100; 0.088000;,
0.341200; 0.569100; 0.088000;,
0.224400; 0.366900; 0.806800;,
0.448100; -0.020600; 0.806800;,
0.681700; -0.020600; 0.088000;,
0.681700; -0.020600; 0.088000;,
0.448100; -0.020600; 0.806800;,
0.224400; -0.408100; 0.806800;,
0.341200; -0.610300; 0.088000;,
0.341200; -0.610300; 0.088000;,
0.224400; -0.408100; 0.806800;,
-0.223000; -0.408100; 0.806800;,
-0.339800; -0.610300; 0.088000;,
-0.339800; -0.610300; 0.088000;,
-0.223000; -0.408100; 0.806800;,
-0.446700; -0.020600; 0.806800;,
-0.680200; -0.020600; 0.088000;,
-0.680200; -0.020600; 0.088000;,
-0.446700; -0.020600; 0.806800;,
-0.223000; 0.366900; 0.806800;,
-0.339800; 0.569100; 0.088000;,
-0.339800; 0.569100; 0.088000;,
-0.223000; 0.366900; 0.806800;,
0.224400; 0.366900; 0.806800;,
0.341200; 0.569100; 0.088000;,
0.448100; -0.020600; 0.806800;,
0.224400; 0.366900; 0.806800;,
0.224400; 0.366900; 1.201700;,
0.448100; -0.020600; 1.201700;,
0.224400; -0.408100; 0.806800;,
0.448100; -0.020600; 0.806800;,
0.448100; -0.020600; 1.201700;,
0.224400; -0.408100; 1.201700;,
-0.223000; -0.408100; 0.806800;,
0.224400; -0.408100; 0.806800;,
0.224400; -0.408100; 1.201700;,
-0.223000; -0.408100; 1.201700;,
-0.446700; -0.020600; 0.806800;,
-0.223000; -0.408100; 0.806800;,
-0.223000; -0.408100; 1.201700;,
-0.446700; -0.020600; 1.201700;,
-0.223000; 0.366900; 0.806800;,
-0.446700; -0.020600; 0.806800;,
-0.446700; -0.020600; 1.201700;,
-0.223000; 0.366900; 1.201700;,
0.224400; 0.366900; 0.806800;,
-0.223000; 0.366900; 0.806800;,
-0.223000; 0.366900; 1.201700;,
0.224400; 0.366900; 1.201700;,
0.448100; -0.020600; 1.201700;,
0.224400; 0.366900; 1.201700;,
0.067100; 0.094500; 1.201700;,
0.133600; -0.020600; 1.201700;,
0.224400; -0.408100; 1.201700;,
0.448100; -0.020600; 1.201700;,
0.133600; -0.020600; 1.201700;,
0.067100; -0.135700; 1.201700;,
-0.223000; -0.408100; 1.201700;,
0.224400; -0.408100; 1.201700;,
0.067100; -0.135700; 1.201700;,
-0.065700; -0.135700; 1.201700;,
-0.446700; -0.020600; 1.201700;,
-0.223000; -0.408100; 1.201700;,
-0.065700; -0.135700; 1.201700;,
-0.132200; -0.020600; 1.201700;,
-0.223000; 0.366900; 1.201700;,
-0.446700; -0.020600; 1.201700;,
-0.132200; -0.020600; 1.201700;,
-0.065700; 0.094500; 1.201700;,
0.224400; 0.366900; 1.201700;,
-0.223000; 0.366900; 1.201700;,
-0.065700; 0.094500; 1.201700;,
0.067100; 0.094500; 1.201700;,
0.133600; -0.020600; 1.201700;,
0.067100; 0.094500; 1.201700;,
0.067600; 0.081600; 1.843000;,
0.134000; -0.033500; 1.843000;,
0.067100; -0.135700; 1.201700;,
0.133600; -0.020600; 1.201700;,
0.134000; -0.033500; 1.843000;,
0.067600; -0.148600; 1.843000;,
-0.065700; -0.135700; 1.201700;,
0.067100; -0.135700; 1.201700;,
0.067600; -0.148600; 1.843000;,
-0.065300; -0.148600; 1.843000;,
-0.132200; -0.020600; 1.201700;,
-0.065700; -0.135700; 1.201700;,
-0.065300; -0.148600; 1.843000;,
-0.131700; -0.033500; 1.843000;,
-0.065700; 0.094500; 1.201700;,
-0.132200; -0.020600; 1.201700;,
-0.131700; -0.033500; 1.843000;,
-0.065300; 0.081600; 1.843000;,
0.067100; 0.094500; 1.201700;,
-0.065700; 0.094500; 1.201700;,
-0.065300; 0.081600; 1.843000;,
0.067600; 0.081600; 1.843000;,
0.134000; -0.033500; 1.843000;,
0.067600; 0.081600; 1.843000;,
0.001200; -0.033500; 1.843000;,
0.067600; -0.148600; 1.843000;,
0.134000; -0.033500; 1.843000;,
0.001200; -0.033500; 1.843000;,
-0.065300; -0.148600; 1.843000;,
0.067600; -0.148600; 1.843000;,
0.001200; -0.033500; 1.843000;,
-0.131700; -0.033500; 1.843000;,
-0.065300; -0.148600; 1.843000;,
0.001200; -0.033500; 1.843000;,
-0.065300; 0.081600; 1.843000;,
-0.131700; -0.033500; 1.843000;,
0.001200; -0.033500; 1.843000;,
0.067600; 0.081600; 1.843000;,
-0.065300; 0.081600; 1.843000;,
0.001200; -0.033500; 1.843000;;
42;
4; 0, 3, 2, 1;,
4; 4, 7, 6, 5;,
4; 8, 11, 10, 9;,
4; 12, 15, 14, 13;,
4; 16, 19, 18, 17;,
4; 20, 23, 22, 21;,
3; 24, 26, 25;,
3; 27, 29, 28;,
3; 30, 32, 31;,
3; 33, 35, 34;,
3; 36, 38, 37;,
3; 39, 41, 40;,
4; 42, 45, 44, 43;,
4; 46, 49, 48, 47;,
4; 50, 53, 52, 51;,
4; 54, 57, 56, 55;,
4; 58, 61, 60, 59;,
4; 62, 65, 64, 63;,
4; 66, 69, 68, 67;,
4; 70, 73, 72, 71;,
4; 74, 77, 76, 75;,
4; 78, 81, 80, 79;,
4; 82, 85, 84, 83;,
4; 86, 89, 88, 87;,
4; 90, 93, 92, 91;,
4; 94, 97, 96, 95;,
4; 98, 101, 100, 99;,
4; 102, 105, 104, 103;,
4; 106, 109, 108, 107;,
4; 110, 113, 112, 111;,
4; 114, 117, 116, 115;,
4; 118, 121, 120, 119;,
4; 122, 125, 124, 123;,
4; 126, 129, 128, 127;,
4; 130, 133, 132, 131;,
4; 134, 137, 136, 135;,
3; 138, 140, 139;,
3; 141, 143, 142;,
3; 144, 146, 145;,
3; 147, 149, 148;,
3; 150, 152, 151;,
3; 153, 155, 154;;
  MeshMaterialList {
    12;
    42;
    0,
    0,
    0,
    0,
    0,
    0,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    9;;
  Material Base_Fire {
    0.700000; 0.700000; 0.700000;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
  Material Lead_One {
    1.000000; 0.000000; 0.000000;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
  Material Lead_Holder_One {
    0.000000; 0.000000; 0.000000;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
  Material Fire3 {
    1.000000; 0.200000; 0.000000;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
  Material Beam1 {
    1.000000; 1.000000; 0.300000;0.40000000596;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
  Material Beam1_001 {
    0.700000; 0.700000; 1.000000;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
  Material Base_Fire {
    0.700000; 0.700000; 0.700000;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
  Material Meteor1_001 {
    0.598066; 0.706049; 0.838910;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
  Material Bolt_Holder {
    0.720354; 0.326957; 0.166326;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
  Material Bolt1 {
    0.695896; 0.803880; 1.000000;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
  Material Bolt_Pipe {
    0.400000; 0.400000; 0.400000;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
  Material Bolt_Pipe_001 {
    0.000000; 0.000000; 0.000000;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
    }  //End of MeshMaterialList
  MeshNormals {
156;
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    1.000000; 0.000000; 0.000000;,
    1.000000; 0.000000; 0.000000;,
    1.000000; 0.000000; 0.000000;,
    1.000000; 0.000000; 0.000000;,
    -0.000000; -1.000000; 0.000000;,
    -0.000000; -1.000000; 0.000000;,
    -0.000000; -1.000000; 0.000000;,
    -0.000000; -1.000000; 0.000000;,
    -1.000000; 0.000000; 0.000000;,
    -1.000000; 0.000000; 0.000000;,
    -1.000000; 0.000000; 0.000000;,
    -1.000000; 0.000000; 0.000000;,
    0.000000; 1.000000; 0.000005;,
    0.000000; 1.000000; 0.000005;,
    0.000000; 1.000000; 0.000005;,
    0.000000; 1.000000; 0.000005;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.833652; 0.481309; 0.270862;,
    0.833652; 0.481309; 0.270862;,
    0.833652; 0.481309; 0.270862;,
    0.833652; 0.481309; 0.270862;,
    0.833652; -0.481309; 0.270862;,
    0.833652; -0.481309; 0.270862;,
    0.833652; -0.481309; 0.270862;,
    0.833652; -0.481309; 0.270862;,
    0.000000; -0.962618; 0.270862;,
    0.000000; -0.962618; 0.270862;,
    0.000000; -0.962618; 0.270862;,
    0.000000; -0.962618; 0.270862;,
    -0.833652; -0.481309; 0.270862;,
    -0.833652; -0.481309; 0.270862;,
    -0.833652; -0.481309; 0.270862;,
    -0.833652; -0.481309; 0.270862;,
    -0.833652; 0.481309; 0.270862;,
    -0.833652; 0.481309; 0.270862;,
    -0.833652; 0.481309; 0.270862;,
    -0.833652; 0.481309; 0.270862;,
    -0.000000; 0.962618; 0.270862;,
    -0.000000; 0.962618; 0.270862;,
    -0.000000; 0.962618; 0.270862;,
    -0.000000; 0.962618; 0.270862;,
    0.866025; 0.500000; 0.000000;,
    0.866025; 0.500000; 0.000000;,
    0.866025; 0.500000; 0.000000;,
    0.866025; 0.500000; 0.000000;,
    0.866026; -0.500000; 0.000000;,
    0.866026; -0.500000; 0.000000;,
    0.866026; -0.500000; 0.000000;,
    0.866026; -0.500000; 0.000000;,
    0.000001; -1.000000; 0.000000;,
    0.000001; -1.000000; 0.000000;,
    0.000001; -1.000000; 0.000000;,
    0.000001; -1.000000; 0.000000;,
    -0.866025; -0.500000; 0.000000;,
    -0.866025; -0.500000; 0.000000;,
    -0.866025; -0.500000; 0.000000;,
    -0.866025; -0.500000; 0.000000;,
    -0.866026; 0.499999; 0.000000;,
    -0.866026; 0.499999; 0.000000;,
    -0.866026; 0.499999; 0.000000;,
    -0.866026; 0.499999; 0.000000;,
    -0.000001; 1.000000; 0.000000;,
    -0.000001; 1.000000; 0.000000;,
    -0.000001; 1.000000; 0.000000;,
    -0.000001; 1.000000; 0.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.865987; 0.499978; 0.009450;,
    0.865987; 0.499978; 0.009450;,
    0.865987; 0.499978; 0.009450;,
    0.865987; 0.499978; 0.009450;,
    0.865976; -0.499971; -0.010653;,
    0.865976; -0.499971; -0.010653;,
    0.865976; -0.499971; -0.010653;,
    0.865976; -0.499971; -0.010653;,
    0.000001; -0.999798; -0.020100;,
    0.000001; -0.999798; -0.020100;,
    0.000001; -0.999798; -0.020100;,
    0.000001; -0.999798; -0.020100;,
    -0.865987; -0.499978; -0.009450;,
    -0.865987; -0.499978; -0.009450;,
    -0.865987; -0.499978; -0.009450;,
    -0.865987; -0.499978; -0.009450;,
    -0.865977; 0.499971; 0.010653;,
    -0.865977; 0.499971; 0.010653;,
    -0.865977; 0.499971; 0.010653;,
    -0.865977; 0.499971; 0.010653;,
    -0.000000; 0.999798; 0.020100;,
    -0.000000; 0.999798; 0.020100;,
    -0.000000; 0.999798; 0.020100;,
    -0.000000; 0.999798; 0.020100;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;;
42;
4; 0, 3, 2, 1;,
4; 4, 7, 6, 5;,
4; 8, 11, 10, 9;,
4; 12, 15, 14, 13;,
4; 16, 19, 18, 17;,
4; 20, 23, 22, 21;,
3; 24, 26, 25;,
3; 27, 29, 28;,
3; 30, 32, 31;,
3; 33, 35, 34;,
3; 36, 38, 37;,
3; 39, 41, 40;,
4; 42, 45, 44, 43;,
4; 46, 49, 48, 47;,
4; 50, 53, 52, 51;,
4; 54, 57, 56, 55;,
4; 58, 61, 60, 59;,
4; 62, 65, 64, 63;,
4; 66, 69, 68, 67;,
4; 70, 73, 72, 71;,
4; 74, 77, 76, 75;,
4; 78, 81, 80, 79;,
4; 82, 85, 84, 83;,
4; 86, 89, 88, 87;,
4; 90, 93, 92, 91;,
4; 94, 97, 96, 95;,
4; 98, 101, 100, 99;,
4; 102, 105, 104, 103;,
4; 106, 109, 108, 107;,
4; 110, 113, 112, 111;,
4; 114, 117, 116, 115;,
4; 118, 121, 120, 119;,
4; 122, 125, 124, 123;,
4; 126, 129, 128, 127;,
4; 130, 133, 132, 131;,
4; 134, 137, 136, 135;,
3; 138, 140, 139;,
3; 141, 143, 142;,
3; 144, 146, 145;,
3; 147, 149, 148;,
3; 150, 152, 151;,
3; 153, 155, 154;;
}  //End of MeshNormals
 }
}
}
