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
Frame Cylinder_003 {

  FrameTransformMatrix {
    1.000000,0.000000,0.000000,0.000000,
    0.000000,1.000000,0.000000,0.000000,
    0.000000,0.000000,1.000000,0.000000,
    0.002900,0.000000,0.000000,1.000000;;
  }
Mesh {
260;
0.000500; 0.373500; 0.000900;,
4.553800; 0.373500; 4.258000;,
6.186400; 0.373500; -0.766800;,
-6.185500; 0.373500; -0.766800;,
-4.552900; 0.373500; 4.258000;,
0.000500; 0.373500; 0.000900;,
0.000500; 0.373500; 0.000900;,
6.186400; 0.373500; -0.766800;,
5.456200; 0.373500; -3.014000;,
-5.455300; 0.373500; -3.014000;,
-6.185500; 0.373500; -0.766800;,
0.000500; 0.373500; 0.000900;,
0.000500; 0.373500; 0.000900;,
5.456200; 0.373500; -3.014000;,
1.181900; 0.373500; -6.119500;,
-1.181000; 0.373500; -6.119500;,
-5.455300; 0.373500; -3.014000;,
0.000500; 0.373500; 0.000900;,
-2.641200; 0.373500; 5.646900;,
2.642100; 0.373500; 5.646900;,
0.000500; 0.373500; 0.000900;,
2.642100; 0.373500; 5.646900;,
4.553800; 0.373500; 4.258000;,
0.000500; 0.373500; 0.000900;,
0.000500; 0.373500; 0.000900;,
-4.552900; 0.373500; 4.258000;,
-2.641200; 0.373500; 5.646900;,
6.186400; 0.373500; -0.766800;,
6.186400; -0.223700; -0.766800;,
5.456200; -0.223700; -3.014000;,
5.456200; 0.373500; -3.014000;,
-5.455300; -0.223700; -3.014000;,
-6.185500; -0.223700; -0.766800;,
-6.185500; 0.373500; -0.766800;,
-5.455300; 0.373500; -3.014000;,
4.553800; -0.223700; 4.258000;,
4.553800; 0.373500; 4.258000;,
2.642100; 0.373500; 5.646900;,
2.642100; -0.223700; 5.646900;,
-2.641200; 0.373500; 5.646900;,
-4.552900; 0.373500; 4.258000;,
-4.552900; -0.223700; 4.258000;,
-2.641200; -0.223700; 5.646900;,
2.642100; -0.223700; 5.646900;,
2.642100; 0.373500; 5.646900;,
1.981700; 0.373500; 6.802900;,
1.981700; -0.223700; 6.802900;,
-1.980800; 0.373500; 6.802900;,
-2.641200; 0.373500; 5.646900;,
-2.641200; -0.223700; 5.646900;,
-1.980800; -0.223700; 6.802900;,
-2.641200; -0.223700; 5.646900;,
2.642100; -0.223700; 5.646900;,
1.981700; -0.223700; 6.802900;,
-1.980800; -0.223700; 6.802900;,
2.642100; 0.373500; 5.646900;,
-2.641200; 0.373500; 5.646900;,
-1.980800; 0.373500; 6.802900;,
1.981700; 0.373500; 6.802900;,
-1.980800; -0.223700; 6.802900;,
1.981700; -0.223700; 6.802900;,
1.981700; 0.373500; 6.802900;,
-1.980800; 0.373500; 6.802900;,
4.553800; 0.373500; 4.258000;,
4.553800; -0.223700; 4.258000;,
5.857300; -0.223700; 3.987100;,
5.857300; 0.373500; 3.987100;,
-5.856400; -0.223700; 3.987100;,
-4.552900; -0.223700; 4.258000;,
-4.552900; 0.373500; 4.258000;,
-5.856400; 0.373500; 3.987100;,
6.186400; -0.223700; -0.766800;,
6.186400; 0.373500; -0.766800;,
7.081800; 0.373500; 0.218600;,
7.081800; -0.223700; 0.218600;,
-7.080800; 0.373500; 0.218600;,
-6.185500; 0.373500; -0.766800;,
-6.185500; -0.223700; -0.766800;,
-7.080800; -0.223700; 0.218600;,
4.553800; -0.223700; 4.258000;,
6.186400; -0.223700; -0.766800;,
7.081800; -0.223700; 0.218600;,
5.857300; -0.223700; 3.987100;,
-7.080800; -0.223700; 0.218600;,
-6.185500; -0.223700; -0.766800;,
-4.552900; -0.223700; 4.258000;,
-5.856400; -0.223700; 3.987100;,
6.186400; 0.373500; -0.766800;,
4.553800; 0.373500; 4.258000;,
5.857300; 0.373500; 3.987100;,
7.081800; 0.373500; 0.218600;,
-5.856400; 0.373500; 3.987100;,
-4.552900; 0.373500; 4.258000;,
-6.185500; 0.373500; -0.766800;,
-7.080800; 0.373500; 0.218600;,
5.857300; 0.373500; 3.987100;,
5.857300; -0.223700; 3.987100;,
7.081800; -0.223700; 0.218600;,
7.081800; 0.373500; 0.218600;,
-7.080800; -0.223700; 0.218600;,
-5.856400; -0.223700; 3.987100;,
-5.856400; 0.373500; 3.987100;,
-7.080800; 0.373500; 0.218600;,
1.181900; -0.223700; -6.119500;,
1.181900; 0.373500; -6.119500;,
2.395700; 0.373500; -6.666500;,
2.395700; -0.223700; -6.666500;,
-2.394800; 0.373500; -6.666500;,
-1.181000; 0.373500; -6.119500;,
-1.181000; -0.223700; -6.119500;,
-2.394800; -0.223700; -6.666500;,
5.456200; 0.373500; -3.014000;,
5.456200; -0.223700; -3.014000;,
5.601400; -0.223700; -4.337500;,
5.601400; 0.373500; -4.337500;,
-5.600500; -0.223700; -4.337500;,
-5.455300; -0.223700; -3.014000;,
-5.455300; 0.373500; -3.014000;,
-5.600500; 0.373500; -4.337500;,
5.456200; -0.223700; -3.014000;,
1.181900; -0.223700; -6.119500;,
2.395700; -0.223700; -6.666500;,
5.601400; -0.223700; -4.337500;,
-2.394800; -0.223700; -6.666500;,
-1.181000; -0.223700; -6.119500;,
-5.455300; -0.223700; -3.014000;,
-5.600500; -0.223700; -4.337500;,
1.181900; 0.373500; -6.119500;,
5.456200; 0.373500; -3.014000;,
5.601400; 0.373500; -4.337500;,
2.395700; 0.373500; -6.666500;,
-5.600500; 0.373500; -4.337500;,
-5.455300; 0.373500; -3.014000;,
-1.181000; 0.373500; -6.119500;,
-2.394800; 0.373500; -6.666500;,
5.601400; 0.373500; -4.337500;,
5.601400; -0.223700; -4.337500;,
2.395700; -0.223700; -6.666500;,
2.395700; 0.373500; -6.666500;,
-2.394800; -0.223700; -6.666500;,
-5.600500; -0.223700; -4.337500;,
-5.600500; 0.373500; -4.337500;,
-2.394800; 0.373500; -6.666500;,
1.181900; 0.373500; -6.119500;,
1.181900; -0.223700; -6.119500;,
-1.181000; -0.223700; -6.119500;,
-1.181000; 0.373500; -6.119500;,
1.181900; 0.373500; -6.119500;,
-1.181000; 0.373500; -6.119500;,
0.000500; 0.373500; 0.000900;,
6.186400; -0.223700; -0.766800;,
4.553800; -0.223700; 4.258000;,
3.336800; -0.223700; 2.731800;,
4.304700; -0.223700; -0.247300;,
-4.552900; -0.223700; 4.258000;,
-6.185500; -0.223700; -0.766800;,
-4.303800; -0.223700; -0.247300;,
-3.335900; -0.223700; 2.731800;,
5.456200; -0.223700; -3.014000;,
6.186400; -0.223700; -0.766800;,
4.304700; -0.223700; -0.247300;,
3.628600; -0.223700; -2.328200;,
-6.185500; -0.223700; -0.766800;,
-5.455300; -0.223700; -3.014000;,
-3.627700; -0.223700; -2.328200;,
-4.303800; -0.223700; -0.247300;,
1.181900; -0.223700; -6.119500;,
5.456200; -0.223700; -3.014000;,
3.628600; -0.223700; -2.328200;,
1.094400; -0.223700; -4.169400;,
2.642100; -0.223700; 5.646900;,
-2.641200; -0.223700; 5.646900;,
-1.565800; -0.223700; 4.017800;,
1.566700; -0.223700; 4.017800;,
-2.641200; -0.223700; 5.646900;,
-4.552900; -0.223700; 4.258000;,
-3.335900; -0.223700; 2.731800;,
-1.565800; -0.223700; 4.017800;,
4.553800; -0.223700; 4.258000;,
2.642100; -0.223700; 5.646900;,
1.566700; -0.223700; 4.017800;,
3.336800; -0.223700; 2.731800;,
-1.181000; -0.223700; -6.119500;,
1.181900; -0.223700; -6.119500;,
1.094400; -0.223700; -4.169400;,
-1.093500; -0.223700; -4.169400;,
-5.455300; -0.223700; -3.014000;,
-1.181000; -0.223700; -6.119500;,
-1.093500; -0.223700; -4.169400;,
-3.627700; -0.223700; -2.328200;,
4.304700; -0.223700; -0.247300;,
3.336800; -0.223700; 2.731800;,
2.370900; -1.006400; 1.941100;,
3.058600; -1.006400; -0.175500;,
-3.335900; -0.223700; 2.731800;,
-4.303800; -0.223700; -0.247300;,
-3.057700; -1.006400; -0.175500;,
-2.370000; -1.006400; 1.941100;,
3.628600; -0.223700; -2.328200;,
4.304700; -0.223700; -0.247300;,
3.058600; -1.006400; -0.175500;,
2.578200; -1.006400; -1.653900;,
-4.303800; -0.223700; -0.247300;,
-3.627700; -0.223700; -2.328200;,
-2.577300; -1.006400; -1.653900;,
-3.057700; -1.006400; -0.175500;,
1.094400; -0.223700; -4.169400;,
3.628600; -0.223700; -2.328200;,
2.578200; -1.006400; -1.653900;,
0.777700; -1.006400; -2.962100;,
1.566700; -0.223700; 4.017800;,
-1.565800; -0.223700; 4.017800;,
-1.112300; -1.006400; 2.854900;,
1.113200; -1.006400; 2.854900;,
-1.565800; -0.223700; 4.017800;,
-3.335900; -0.223700; 2.731800;,
-2.370000; -1.006400; 1.941100;,
-1.112300; -1.006400; 2.854900;,
3.336800; -0.223700; 2.731800;,
1.566700; -0.223700; 4.017800;,
1.113200; -1.006400; 2.854900;,
2.370900; -1.006400; 1.941100;,
-1.093500; -0.223700; -4.169400;,
1.094400; -0.223700; -4.169400;,
0.777700; -1.006400; -2.962100;,
-0.776800; -1.006400; -2.962100;,
-3.627700; -0.223700; -2.328200;,
-1.093500; -0.223700; -4.169400;,
-0.776800; -1.006400; -2.962100;,
-2.577300; -1.006400; -1.653900;,
3.058600; -1.006400; -0.175500;,
2.370900; -1.006400; 1.941100;,
0.000500; -1.006400; 0.000900;,
-2.370000; -1.006400; 1.941100;,
-3.057700; -1.006400; -0.175500;,
0.000500; -1.006400; 0.000900;,
2.578200; -1.006400; -1.653900;,
3.058600; -1.006400; -0.175500;,
0.000500; -1.006400; 0.000900;,
-3.057700; -1.006400; -0.175500;,
-2.577300; -1.006400; -1.653900;,
0.000500; -1.006400; 0.000900;,
0.777700; -1.006400; -2.962100;,
2.578200; -1.006400; -1.653900;,
0.000500; -1.006400; 0.000900;,
1.113200; -1.006400; 2.854900;,
-1.112300; -1.006400; 2.854900;,
0.000500; -1.006400; 0.000900;,
-1.112300; -1.006400; 2.854900;,
-2.370000; -1.006400; 1.941100;,
0.000500; -1.006400; 0.000900;,
2.370900; -1.006400; 1.941100;,
1.113200; -1.006400; 2.854900;,
0.000500; -1.006400; 0.000900;,
-0.776800; -1.006400; -2.962100;,
0.777700; -1.006400; -2.962100;,
0.000500; -1.006400; 0.000900;,
-2.577300; -1.006400; -1.653900;,
-0.776800; -1.006400; -2.962100;,
0.000500; -1.006400; 0.000900;;
70;
3; 0, 2, 1;,
3; 3, 5, 4;,
3; 6, 8, 7;,
3; 9, 11, 10;,
3; 12, 14, 13;,
3; 15, 17, 16;,
3; 18, 20, 19;,
3; 21, 23, 22;,
3; 24, 26, 25;,
4; 27, 30, 29, 28;,
4; 31, 34, 33, 32;,
4; 35, 38, 37, 36;,
4; 39, 42, 41, 40;,
4; 43, 46, 45, 44;,
4; 47, 50, 49, 48;,
4; 51, 54, 53, 52;,
4; 55, 58, 57, 56;,
4; 59, 62, 61, 60;,
4; 63, 66, 65, 64;,
4; 67, 70, 69, 68;,
4; 71, 74, 73, 72;,
4; 75, 78, 77, 76;,
4; 79, 82, 81, 80;,
4; 83, 86, 85, 84;,
4; 87, 90, 89, 88;,
4; 91, 94, 93, 92;,
4; 95, 98, 97, 96;,
4; 99, 102, 101, 100;,
4; 103, 106, 105, 104;,
4; 107, 110, 109, 108;,
4; 111, 114, 113, 112;,
4; 115, 118, 117, 116;,
4; 119, 122, 121, 120;,
4; 123, 126, 125, 124;,
4; 127, 130, 129, 128;,
4; 131, 134, 133, 132;,
4; 135, 138, 137, 136;,
4; 139, 142, 141, 140;,
4; 143, 146, 145, 144;,
3; 147, 149, 148;,
4; 150, 153, 152, 151;,
4; 154, 157, 156, 155;,
4; 158, 161, 160, 159;,
4; 162, 165, 164, 163;,
4; 166, 169, 168, 167;,
4; 170, 173, 172, 171;,
4; 174, 177, 176, 175;,
4; 178, 181, 180, 179;,
4; 182, 185, 184, 183;,
4; 186, 189, 188, 187;,
4; 190, 193, 192, 191;,
4; 194, 197, 196, 195;,
4; 198, 201, 200, 199;,
4; 202, 205, 204, 203;,
4; 206, 209, 208, 207;,
4; 210, 213, 212, 211;,
4; 214, 217, 216, 215;,
4; 218, 221, 220, 219;,
4; 222, 225, 224, 223;,
4; 226, 229, 228, 227;,
3; 230, 232, 231;,
3; 233, 235, 234;,
3; 236, 238, 237;,
3; 239, 241, 240;,
3; 242, 244, 243;,
3; 245, 247, 246;,
3; 248, 250, 249;,
3; 251, 253, 252;,
3; 254, 256, 255;,
3; 257, 259, 258;;
  MeshMaterialList {
    2;
    70;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;;
  Material Material_001 {
    1.000000; 1.000000; 1.000000;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
  Material Mat1 {
    1.0; 1.0; 1.0; 1.0;;
    1.0;
    1.0; 1.0; 1.0;;
    0.0; 0.0; 0.0;;
  TextureFilename {    "MenuCog.png";  }
  }  // End of Material
    }  //End of MeshMaterialList
  MeshNormals {
260;
    -0.000001; 1.000000; 0.000002;,
    -0.000001; 1.000000; 0.000002;,
    -0.000001; 1.000000; 0.000002;,
    -0.000000; 1.000000; -0.000000;,
    -0.000000; 1.000000; -0.000000;,
    -0.000000; 1.000000; -0.000000;,
    -0.000001; 1.000000; -0.000005;,
    -0.000001; 1.000000; -0.000005;,
    -0.000001; 1.000000; -0.000005;,
    -0.000000; 1.000000; 0.000000;,
    -0.000000; 1.000000; 0.000000;,
    -0.000000; 1.000000; 0.000000;,
    0.000002; 1.000000; 0.000002;,
    0.000002; 1.000000; 0.000002;,
    0.000002; 1.000000; 0.000002;,
    0.000000; 1.000000; -0.000000;,
    0.000000; 1.000000; -0.000000;,
    0.000000; 1.000000; -0.000000;,
    0.000000; 1.000000; 0.000000;,
    0.000000; 1.000000; 0.000000;,
    0.000000; 1.000000; 0.000000;,
    0.000002; 1.000000; -0.000001;,
    0.000002; 1.000000; -0.000001;,
    0.000002; 1.000000; -0.000001;,
    0.000000; 1.000000; 0.000000;,
    0.000000; 1.000000; 0.000000;,
    0.000000; 1.000000; 0.000000;,
    0.951056; 0.000002; -0.309017;,
    0.951056; 0.000002; -0.309017;,
    0.951056; 0.000002; -0.309017;,
    0.951056; 0.000002; -0.309017;,
    -0.951056; 0.000000; -0.309017;,
    -0.951056; 0.000000; -0.309017;,
    -0.951056; 0.000000; -0.309017;,
    -0.951056; 0.000000; -0.309017;,
    0.587786; -0.000004; 0.809017;,
    0.587786; -0.000004; 0.809017;,
    0.587786; -0.000004; 0.809017;,
    0.587786; -0.000004; 0.809017;,
    -0.587787; 0.000002; 0.809016;,
    -0.587787; 0.000002; 0.809016;,
    -0.587787; 0.000002; 0.809016;,
    -0.587787; 0.000002; 0.809016;,
    0.868295; -0.000021; 0.496049;,
    0.868295; -0.000021; 0.496049;,
    0.868295; -0.000021; 0.496049;,
    0.868295; -0.000021; 0.496049;,
    -0.868296; 0.000021; 0.496047;,
    -0.868296; 0.000021; 0.496047;,
    -0.868296; 0.000021; 0.496047;,
    -0.868296; 0.000021; 0.496047;,
    0.000000; -1.000000; -0.000000;,
    0.000000; -1.000000; -0.000000;,
    0.000000; -1.000000; -0.000000;,
    0.000000; -1.000000; -0.000000;,
    -0.000000; 1.000000; -0.000000;,
    -0.000000; 1.000000; -0.000000;,
    -0.000000; 1.000000; -0.000000;,
    -0.000000; 1.000000; -0.000000;,
    -0.000001; 0.000000; 1.000000;,
    -0.000001; 0.000000; 1.000000;,
    -0.000001; 0.000000; 1.000000;,
    -0.000001; 0.000000; 1.000000;,
    0.203453; -0.000005; 0.979085;,
    0.203453; -0.000005; 0.979085;,
    0.203453; -0.000005; 0.979085;,
    0.203453; -0.000005; 0.979085;,
    -0.203453; -0.000009; 0.979085;,
    -0.203453; -0.000009; 0.979085;,
    -0.203453; -0.000009; 0.979085;,
    -0.203453; -0.000009; 0.979085;,
    0.740088; 0.000008; -0.672511;,
    0.740088; 0.000008; -0.672511;,
    0.740088; 0.000008; -0.672511;,
    0.740088; 0.000008; -0.672511;,
    -0.740087; 0.000011; -0.672511;,
    -0.740087; 0.000011; -0.672511;,
    -0.740087; 0.000011; -0.672511;,
    -0.740087; 0.000011; -0.672511;,
    0.000001; -1.000000; -0.000002;,
    0.000001; -1.000000; -0.000002;,
    0.000001; -1.000000; -0.000002;,
    0.000001; -1.000000; -0.000002;,
    0.000000; -1.000000; 0.000000;,
    0.000000; -1.000000; 0.000000;,
    0.000000; -1.000000; 0.000000;,
    0.000000; -1.000000; 0.000000;,
    -0.000001; 1.000000; 0.000002;,
    -0.000001; 1.000000; 0.000002;,
    -0.000001; 1.000000; 0.000002;,
    -0.000001; 1.000000; 0.000002;,
    -0.000000; 1.000000; -0.000000;,
    -0.000000; 1.000000; -0.000000;,
    -0.000000; 1.000000; -0.000000;,
    -0.000000; 1.000000; -0.000000;,
    0.951057; -0.000001; 0.309016;,
    0.951057; -0.000001; 0.309016;,
    0.951057; -0.000001; 0.309016;,
    0.951057; -0.000001; 0.309016;,
    -0.951057; -0.000000; 0.309016;,
    -0.951057; -0.000000; 0.309016;,
    -0.951057; -0.000000; 0.309016;,
    -0.951057; -0.000000; 0.309016;,
    -0.410896; 0.000009; -0.911682;,
    -0.410896; 0.000009; -0.911682;,
    -0.410896; 0.000009; -0.911682;,
    -0.410896; 0.000009; -0.911682;,
    0.410896; 0.000014; -0.911682;,
    0.410896; 0.000014; -0.911682;,
    0.410896; 0.000014; -0.911682;,
    0.410896; 0.000014; -0.911682;,
    0.994035; -0.000008; 0.109058;,
    0.994035; -0.000008; 0.109058;,
    0.994035; -0.000008; 0.109058;,
    0.994035; -0.000008; 0.109058;,
    -0.994035; -0.000013; 0.109058;,
    -0.994035; -0.000013; 0.109058;,
    -0.994035; -0.000013; 0.109058;,
    -0.994035; -0.000013; 0.109058;,
    -0.000002; -1.000000; -0.000002;,
    -0.000002; -1.000000; -0.000002;,
    -0.000002; -1.000000; -0.000002;,
    -0.000002; -1.000000; -0.000002;,
    -0.000000; -1.000000; 0.000000;,
    -0.000000; -1.000000; 0.000000;,
    -0.000000; -1.000000; 0.000000;,
    -0.000000; -1.000000; 0.000000;,
    0.000002; 1.000000; 0.000002;,
    0.000002; 1.000000; 0.000002;,
    0.000002; 1.000000; 0.000002;,
    0.000002; 1.000000; 0.000002;,
    0.000000; 1.000000; 0.000000;,
    0.000000; 1.000000; 0.000000;,
    0.000000; 1.000000; 0.000000;,
    0.000000; 1.000000; 0.000000;,
    0.587784; -0.000000; -0.809018;,
    0.587784; -0.000000; -0.809018;,
    0.587784; -0.000000; -0.809018;,
    0.587784; -0.000000; -0.809018;,
    -0.587784; -0.000001; -0.809018;,
    -0.587784; -0.000001; -0.809018;,
    -0.587784; -0.000001; -0.809018;,
    -0.587784; -0.000001; -0.809018;,
    0.000000; 0.000004; -1.000000;,
    0.000000; 0.000004; -1.000000;,
    0.000000; 0.000004; -1.000000;,
    0.000000; 0.000004; -1.000000;,
    -0.000003; 1.000000; 0.000001;,
    -0.000003; 1.000000; 0.000001;,
    -0.000003; 1.000000; 0.000001;,
    0.000000; -1.000000; -0.000001;,
    0.000000; -1.000000; -0.000001;,
    0.000000; -1.000000; -0.000001;,
    0.000000; -1.000000; -0.000001;,
    0.000000; -1.000000; 0.000000;,
    0.000000; -1.000000; 0.000000;,
    0.000000; -1.000000; 0.000000;,
    0.000000; -1.000000; 0.000000;,
    0.000000; -1.000000; 0.000003;,
    0.000000; -1.000000; 0.000003;,
    0.000000; -1.000000; 0.000003;,
    0.000000; -1.000000; 0.000003;,
    0.000000; -1.000000; -0.000000;,
    0.000000; -1.000000; -0.000000;,
    0.000000; -1.000000; -0.000000;,
    0.000000; -1.000000; -0.000000;,
    -0.000002; -1.000000; -0.000001;,
    -0.000002; -1.000000; -0.000001;,
    -0.000002; -1.000000; -0.000001;,
    -0.000002; -1.000000; -0.000001;,
    0.000000; -1.000000; 0.000000;,
    0.000000; -1.000000; 0.000000;,
    0.000000; -1.000000; 0.000000;,
    0.000000; -1.000000; 0.000000;,
    -0.000000; -1.000000; 0.000000;,
    -0.000000; -1.000000; 0.000000;,
    -0.000000; -1.000000; 0.000000;,
    -0.000000; -1.000000; 0.000000;,
    -0.000001; -1.000000; -0.000000;,
    -0.000001; -1.000000; -0.000000;,
    -0.000001; -1.000000; -0.000000;,
    -0.000001; -1.000000; -0.000000;,
    0.000002; -1.000000; -0.000002;,
    0.000002; -1.000000; -0.000002;,
    0.000002; -1.000000; -0.000002;,
    0.000002; -1.000000; -0.000002;,
    -0.000000; -1.000000; -0.000000;,
    -0.000000; -1.000000; -0.000000;,
    -0.000000; -1.000000; -0.000000;,
    -0.000000; -1.000000; -0.000000;,
    0.531050; -0.829587; 0.172548;,
    0.531050; -0.829587; 0.172548;,
    0.531050; -0.829587; 0.172548;,
    0.531050; -0.829587; 0.172548;,
    -0.531050; -0.829586; 0.172548;,
    -0.531050; -0.829586; 0.172548;,
    -0.531050; -0.829586; 0.172548;,
    -0.531050; -0.829586; 0.172548;,
    0.517370; -0.839088; -0.168104;,
    0.517370; -0.839088; -0.168104;,
    0.517370; -0.839088; -0.168104;,
    0.517370; -0.839088; -0.168104;,
    -0.517370; -0.839088; -0.168105;,
    -0.517370; -0.839088; -0.168105;,
    -0.517370; -0.839088; -0.168105;,
    -0.517370; -0.839088; -0.168105;,
    0.328205; -0.829586; -0.451739;,
    0.328205; -0.829586; -0.451739;,
    0.328205; -0.829586; -0.451739;,
    0.328205; -0.829586; -0.451739;,
    -0.000001; -0.829587; 0.558378;,
    -0.000001; -0.829587; 0.558378;,
    -0.000001; -0.829587; 0.558378;,
    -0.000001; -0.829587; 0.558378;,
    -0.319753; -0.839089; 0.440100;,
    -0.319753; -0.839089; 0.440100;,
    -0.319753; -0.839089; 0.440100;,
    -0.319753; -0.839089; 0.440100;,
    0.319752; -0.839089; 0.440101;,
    0.319752; -0.839089; 0.440101;,
    0.319752; -0.839089; 0.440101;,
    0.319752; -0.839089; 0.440101;,
    0.000000; -0.839088; -0.543995;,
    0.000000; -0.839088; -0.543995;,
    0.000000; -0.839088; -0.543995;,
    0.000000; -0.839088; -0.543995;,
    -0.328206; -0.829586; -0.451739;,
    -0.328206; -0.829586; -0.451739;,
    -0.328206; -0.829586; -0.451739;,
    -0.328206; -0.829586; -0.451739;,
    0.000000; -1.000000; -0.000000;,
    0.000000; -1.000000; -0.000000;,
    0.000000; -1.000000; -0.000000;,
    -0.000000; -1.000000; 0.000000;,
    -0.000000; -1.000000; 0.000000;,
    -0.000000; -1.000000; 0.000000;,
    0.000000; -1.000000; 0.000001;,
    0.000000; -1.000000; 0.000001;,
    0.000000; -1.000000; 0.000001;,
    -0.000000; -1.000000; -0.000000;,
    -0.000000; -1.000000; -0.000000;,
    -0.000000; -1.000000; -0.000000;,
    -0.000000; -1.000000; -0.000000;,
    -0.000000; -1.000000; -0.000000;,
    -0.000000; -1.000000; -0.000000;,
    -0.000000; -1.000000; 0.000000;,
    -0.000000; -1.000000; 0.000000;,
    -0.000000; -1.000000; 0.000000;,
    -0.000000; -1.000000; 0.000000;,
    -0.000000; -1.000000; 0.000000;,
    -0.000000; -1.000000; 0.000000;,
    -0.000000; -1.000000; 0.000000;,
    -0.000000; -1.000000; 0.000000;,
    -0.000000; -1.000000; 0.000000;,
    0.000000; -1.000000; -0.000000;,
    0.000000; -1.000000; -0.000000;,
    0.000000; -1.000000; -0.000000;,
    -0.000000; -1.000000; -0.000000;,
    -0.000000; -1.000000; -0.000000;,
    -0.000000; -1.000000; -0.000000;;
70;
3; 0, 2, 1;,
3; 3, 5, 4;,
3; 6, 8, 7;,
3; 9, 11, 10;,
3; 12, 14, 13;,
3; 15, 17, 16;,
3; 18, 20, 19;,
3; 21, 23, 22;,
3; 24, 26, 25;,
4; 27, 30, 29, 28;,
4; 31, 34, 33, 32;,
4; 35, 38, 37, 36;,
4; 39, 42, 41, 40;,
4; 43, 46, 45, 44;,
4; 47, 50, 49, 48;,
4; 51, 54, 53, 52;,
4; 55, 58, 57, 56;,
4; 59, 62, 61, 60;,
4; 63, 66, 65, 64;,
4; 67, 70, 69, 68;,
4; 71, 74, 73, 72;,
4; 75, 78, 77, 76;,
4; 79, 82, 81, 80;,
4; 83, 86, 85, 84;,
4; 87, 90, 89, 88;,
4; 91, 94, 93, 92;,
4; 95, 98, 97, 96;,
4; 99, 102, 101, 100;,
4; 103, 106, 105, 104;,
4; 107, 110, 109, 108;,
4; 111, 114, 113, 112;,
4; 115, 118, 117, 116;,
4; 119, 122, 121, 120;,
4; 123, 126, 125, 124;,
4; 127, 130, 129, 128;,
4; 131, 134, 133, 132;,
4; 135, 138, 137, 136;,
4; 139, 142, 141, 140;,
4; 143, 146, 145, 144;,
3; 147, 149, 148;,
4; 150, 153, 152, 151;,
4; 154, 157, 156, 155;,
4; 158, 161, 160, 159;,
4; 162, 165, 164, 163;,
4; 166, 169, 168, 167;,
4; 170, 173, 172, 171;,
4; 174, 177, 176, 175;,
4; 178, 181, 180, 179;,
4; 182, 185, 184, 183;,
4; 186, 189, 188, 187;,
4; 190, 193, 192, 191;,
4; 194, 197, 196, 195;,
4; 198, 201, 200, 199;,
4; 202, 205, 204, 203;,
4; 206, 209, 208, 207;,
4; 210, 213, 212, 211;,
4; 214, 217, 216, 215;,
4; 218, 221, 220, 219;,
4; 222, 225, 224, 223;,
4; 226, 229, 228, 227;,
3; 230, 232, 231;,
3; 233, 235, 234;,
3; 236, 238, 237;,
3; 239, 241, 240;,
3; 242, 244, 243;,
3; 245, 247, 246;,
3; 248, 250, 249;,
3; 251, 253, 252;,
3; 254, 256, 255;,
3; 257, 259, 258;;
}  //End of MeshNormals
MeshTextureCoords {
260;
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
-0.128230;-0.674871;,
1.121770;-0.674871;,
0.965520;-0.838974;,
0.028020;-0.838973;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
-0.119958;-0.504282;,
1.124594;-0.504282;,
0.969025;-0.667669;,
0.035611;-0.667669;,
0.024922;-0.171053;,
-0.131911;-0.006338;,
1.122752;-0.006338;,
0.965919;-0.171053;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
-0.127641;-0.336011;,
1.118623;-0.336011;,
0.962840;-0.499623;,
0.028142;-0.499623;,
0.058261;-0.334323;,
-0.097964;-0.170248;,
1.151830;-0.170248;,
0.995606;-0.334323;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
-0.119958;-0.504282;,
1.124594;-0.504282;,
0.969025;-0.667669;,
0.035611;-0.667669;,
0.024922;-0.171053;,
-0.131911;-0.006338;,
1.122752;-0.006338;,
0.965919;-0.171053;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
-0.127641;-0.336011;,
1.118623;-0.336011;,
0.962840;-0.499623;,
0.028142;-0.499623;,
-0.128230;-0.674871;,
1.121770;-0.674871;,
0.965520;-0.838974;,
0.028020;-0.838973;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.058261;-0.334323;,
-0.097964;-0.170248;,
1.151830;-0.170248;,
0.995606;-0.334323;,
-0.119958;-0.504282;,
1.124594;-0.504282;,
0.969025;-0.667669;,
0.035611;-0.667669;,
0.024922;-0.171053;,
-0.131911;-0.006338;,
1.122752;-0.006338;,
0.965919;-0.171053;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
-0.127641;-0.336011;,
1.118623;-0.336011;,
0.962840;-0.499623;,
0.028142;-0.499623;,
-0.128230;-0.674871;,
1.121770;-0.674871;,
0.965520;-0.838974;,
0.028020;-0.838973;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-1.000000;,
0.058261;-0.334323;,
-0.097964;-0.170248;,
1.151830;-0.170248;,
0.995606;-0.334323;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.024922;-0.171053;,
-0.131911;-0.006338;,
1.122752;-0.006338;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
-0.127641;-0.336011;,
1.118623;-0.336011;,
0.962840;-0.499623;,
-0.128230;-0.674871;,
1.121770;-0.674871;,
0.965520;-0.838974;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-1.000000;,
0.058261;-0.334323;,
-0.097964;-0.170248;,
1.151830;-0.170248;;
}  //End of MeshTextureCoords
 }
}
}
