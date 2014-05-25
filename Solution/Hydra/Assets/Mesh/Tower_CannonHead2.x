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
Frame Cube_012 {

  FrameTransformMatrix {
    1.000000,0.000000,0.000000,0.000000,
    0.000000,1.000000,0.000000,0.000000,
    0.000000,0.000000,1.000000,0.000000,
    0.000000,0.000000,0.000000,1.000000;;
  }
Mesh {
150;
0.000600; 0.589500; 2.221500;,
0.000600; 1.077900; 2.080500;,
-0.134900; 1.050600; 1.985800;,
-0.134900; 0.562100; 2.126900;,
0.136200; 0.562100; 2.126900;,
0.136200; 1.050600; 1.985800;,
0.000600; 1.077900; 2.080500;,
0.000600; 0.589500; 2.221500;,
0.084400; 0.517900; 1.973800;,
0.084400; 1.006300; 1.832700;,
0.136200; 1.050600; 1.985800;,
0.136200; 0.562100; 2.126900;,
-0.083200; 0.517900; 1.973800;,
-0.083200; 1.006300; 1.832700;,
0.084400; 1.006300; 1.832700;,
0.084400; 0.517900; 1.973800;,
-0.134900; 0.562100; 2.126900;,
-0.134900; 1.050600; 1.985800;,
-0.083200; 1.006300; 1.832700;,
-0.083200; 0.517900; 1.973800;,
0.000600; 0.549900; 2.084600;,
0.000600; 0.589500; 2.221500;,
-0.134900; 0.562100; 2.126900;,
0.000600; 0.549900; 2.084600;,
0.136200; 0.562100; 2.126900;,
0.000600; 0.589500; 2.221500;,
0.000600; 0.549900; 2.084600;,
0.084400; 0.517900; 1.973800;,
0.136200; 0.562100; 2.126900;,
0.000600; 0.549900; 2.084600;,
-0.083200; 0.517900; 1.973800;,
0.084400; 0.517900; 1.973800;,
0.000600; 0.549900; 2.084600;,
-0.134900; 0.562100; 2.126900;,
-0.083200; 0.517900; 1.973800;,
0.368300; -0.624700; 1.948700;,
-0.361300; -0.624700; 1.948700;,
0.003500; 0.007100; 1.949500;,
0.733100; 0.007100; 1.948700;,
0.368300; -0.624700; 1.948700;,
0.003500; 0.007100; 1.949500;,
0.368300; 0.639000; 1.948700;,
0.733100; 0.007100; 1.948700;,
0.003500; 0.007100; 1.949500;,
-0.361300; 0.639000; 1.948700;,
0.368300; 0.639000; 1.948700;,
0.003500; 0.007100; 1.949500;,
-0.726100; 0.007100; 1.948700;,
-0.361300; 0.639000; 1.948700;,
0.003500; 0.007100; 1.949500;,
-0.361300; -0.624700; 1.948700;,
-0.726100; 0.007100; 1.948700;,
0.003500; 0.007100; 1.949500;,
0.368300; -0.624700; 2.157100;,
-0.361300; -0.624700; 2.156700;,
-0.361300; -0.624700; 1.948700;,
0.368300; -0.624700; 1.948700;,
0.733100; 0.007100; 2.156700;,
0.368300; -0.624700; 2.157100;,
0.368300; -0.624700; 1.948700;,
0.733100; 0.007100; 1.948700;,
0.368300; 0.639000; 2.156700;,
0.733100; 0.007100; 2.156700;,
0.733100; 0.007100; 1.948700;,
0.368300; 0.639000; 1.948700;,
-0.361300; 0.639000; 2.156700;,
0.368300; 0.639000; 2.156700;,
0.368300; 0.639000; 1.948700;,
-0.361300; 0.639000; 1.948700;,
-0.726100; 0.007100; 2.156700;,
-0.361300; 0.639000; 2.156700;,
-0.361300; 0.639000; 1.948700;,
-0.726100; 0.007100; 1.948700;,
-0.361300; -0.624700; 2.156700;,
-0.726100; 0.007100; 2.156700;,
-0.726100; 0.007100; 1.948700;,
-0.361300; -0.624700; 1.948700;,
0.003500; 0.007100; 2.157100;,
-0.361300; -0.624700; 2.156700;,
0.368300; -0.624700; 2.157100;,
0.003500; 0.007100; 2.157100;,
0.368300; -0.624700; 2.157100;,
0.733100; 0.007100; 2.156700;,
0.003500; 0.007100; 2.157100;,
0.733100; 0.007100; 2.156700;,
0.368300; 0.639000; 2.156700;,
0.003500; 0.007100; 2.157100;,
0.368300; 0.639000; 2.156700;,
-0.361300; 0.639000; 2.156700;,
0.003500; 0.007100; 2.157100;,
-0.361300; 0.639000; 2.156700;,
-0.726100; 0.007100; 2.156700;,
0.003500; 0.007100; 2.157100;,
-0.726100; 0.007100; 2.156700;,
-0.361300; -0.624700; 2.156700;,
-0.083200; 1.006300; 1.832700;,
-0.134900; 1.050600; 1.985800;,
-0.096900; 1.047100; 1.973900;,
-0.059600; 1.015300; 1.863800;,
0.084400; 1.006300; 1.832700;,
-0.083200; 1.006300; 1.832700;,
-0.059600; 1.015300; 1.863800;,
0.060900; 1.015300; 1.863800;,
0.136200; 1.050600; 1.985800;,
0.084400; 1.006300; 1.832700;,
0.060900; 1.015300; 1.863800;,
0.098100; 1.047100; 1.973900;,
0.000600; 1.077900; 2.080500;,
0.136200; 1.050600; 1.985800;,
0.098100; 1.047100; 1.973900;,
0.000600; 1.066800; 2.042000;,
-0.134900; 1.050600; 1.985800;,
0.000600; 1.077900; 2.080500;,
0.000600; 1.066800; 2.042000;,
-0.096900; 1.047100; 1.973900;,
-0.096900; 1.047100; 1.973900;,
0.000600; 1.066800; 2.042000;,
0.000600; 1.016400; 2.056600;,
-0.096900; 0.996700; 1.988500;,
0.000600; 1.066800; 2.042000;,
0.098100; 1.047100; 1.973900;,
0.098100; 0.996700; 1.988500;,
0.000600; 1.016400; 2.056600;,
0.098100; 1.047100; 1.973900;,
0.060900; 1.015300; 1.863800;,
0.060900; 0.964900; 1.878400;,
0.098100; 0.996700; 1.988500;,
0.060900; 1.015300; 1.863800;,
-0.059600; 1.015300; 1.863800;,
-0.059600; 0.964900; 1.878400;,
0.060900; 0.964900; 1.878400;,
-0.059600; 1.015300; 1.863800;,
-0.096900; 1.047100; 1.973900;,
-0.096900; 0.996700; 1.988500;,
-0.059600; 0.964900; 1.878400;,
0.000600; 0.987900; 1.958100;,
-0.096900; 0.996700; 1.988500;,
0.000600; 1.016400; 2.056600;,
0.000600; 0.987900; 1.958100;,
0.000600; 1.016400; 2.056600;,
0.098100; 0.996700; 1.988500;,
0.000600; 0.987900; 1.958100;,
0.098100; 0.996700; 1.988500;,
0.060900; 0.964900; 1.878400;,
0.000600; 0.987900; 1.958100;,
0.060900; 0.964900; 1.878400;,
-0.059600; 0.964900; 1.878400;,
0.000600; 0.987900; 1.958100;,
-0.059600; 0.964900; 1.878400;,
-0.096900; 0.996700; 1.988500;;
43;
4; 0, 3, 2, 1;,
4; 4, 7, 6, 5;,
4; 8, 11, 10, 9;,
4; 12, 15, 14, 13;,
4; 16, 19, 18, 17;,
3; 20, 22, 21;,
3; 23, 25, 24;,
3; 26, 28, 27;,
3; 29, 31, 30;,
3; 32, 34, 33;,
3; 35, 37, 36;,
3; 38, 40, 39;,
3; 41, 43, 42;,
3; 44, 46, 45;,
3; 47, 49, 48;,
3; 50, 52, 51;,
4; 53, 56, 55, 54;,
4; 57, 60, 59, 58;,
4; 61, 64, 63, 62;,
4; 65, 68, 67, 66;,
4; 69, 72, 71, 70;,
4; 73, 76, 75, 74;,
3; 77, 79, 78;,
3; 80, 82, 81;,
3; 83, 85, 84;,
3; 86, 88, 87;,
3; 89, 91, 90;,
3; 92, 94, 93;,
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
3; 135, 137, 136;,
3; 138, 140, 139;,
3; 141, 143, 142;,
3; 144, 146, 145;,
3; 147, 149, 148;;
  MeshMaterialList {
    5;
    43;
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4;;
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
  Material CannonHead2 {
    1.000000; 1.000000; 0.800000;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
    }  //End of MeshMaterialList
  MeshNormals {
150;
    -0.587784; 0.224490; 0.777248;,
    -0.587784; 0.224490; 0.777248;,
    -0.587784; 0.224490; 0.777248;,
    -0.587784; 0.224490; 0.777248;,
    0.587784; 0.224490; 0.777248;,
    0.587784; 0.224490; 0.777248;,
    0.587784; 0.224490; 0.777248;,
    0.587784; 0.224490; 0.777248;,
    0.951057; -0.085748; -0.296882;,
    0.951057; -0.085748; -0.296882;,
    0.951057; -0.085748; -0.296882;,
    0.951057; -0.085748; -0.296882;,
    0.000000; -0.277485; -0.960730;,
    0.000000; -0.277485; -0.960730;,
    0.000000; -0.277485; -0.960730;,
    0.000000; -0.277485; -0.960730;,
    -0.951056; -0.085748; -0.296882;,
    -0.951056; -0.085748; -0.296882;,
    -0.951056; -0.085748; -0.296882;,
    -0.951056; -0.085748; -0.296882;,
    0.000000; -0.960730; 0.277485;,
    0.000000; -0.960730; 0.277485;,
    0.000000; -0.960730; 0.277485;,
    -0.000000; -0.960730; 0.277485;,
    -0.000000; -0.960730; 0.277485;,
    -0.000000; -0.960730; 0.277485;,
    -0.000000; -0.960730; 0.277485;,
    -0.000000; -0.960730; 0.277485;,
    -0.000000; -0.960730; 0.277485;,
    0.000000; -0.960730; 0.277485;,
    0.000000; -0.960730; 0.277485;,
    0.000000; -0.960730; 0.277485;,
    0.000000; -0.960730; 0.277485;,
    0.000000; -0.960730; 0.277485;,
    0.000000; -0.960730; 0.277485;,
    -0.000000; 0.001183; -0.999999;,
    -0.000000; 0.001183; -0.999999;,
    -0.000000; 0.001183; -0.999999;,
    -0.001024; 0.000591; -0.999999;,
    -0.001024; 0.000591; -0.999999;,
    -0.001024; 0.000591; -0.999999;,
    -0.001024; -0.000591; -0.999999;,
    -0.001024; -0.000591; -0.999999;,
    -0.001024; -0.000591; -0.999999;,
    -0.000000; -0.001183; -0.999999;,
    -0.000000; -0.001183; -0.999999;,
    -0.000000; -0.001183; -0.999999;,
    0.001024; -0.000591; -0.999999;,
    0.001024; -0.000591; -0.999999;,
    0.001024; -0.000591; -0.999999;,
    0.001024; 0.000591; -0.999999;,
    0.001024; 0.000591; -0.999999;,
    0.001024; 0.000591; -0.999999;,
    0.000003; -1.000000; 0.000000;,
    0.000003; -1.000000; 0.000000;,
    0.000003; -1.000000; 0.000000;,
    0.000003; -1.000000; 0.000000;,
    0.866025; -0.500000; 0.000000;,
    0.866025; -0.500000; 0.000000;,
    0.866025; -0.500000; 0.000000;,
    0.866025; -0.500000; 0.000000;,
    0.866025; 0.500000; 0.000000;,
    0.866025; 0.500000; 0.000000;,
    0.866025; 0.500000; 0.000000;,
    0.866025; 0.500000; 0.000000;,
    0.000000; 1.000000; 0.000000;,
    0.000000; 1.000000; 0.000000;,
    0.000000; 1.000000; 0.000000;,
    0.000000; 1.000000; 0.000000;,
    -0.866026; 0.499999; 0.000000;,
    -0.866026; 0.499999; 0.000000;,
    -0.866026; 0.499999; 0.000000;,
    -0.866026; 0.499999; 0.000000;,
    -0.866026; -0.499999; 0.000000;,
    -0.866026; -0.499999; 0.000000;,
    -0.866026; -0.499999; 0.000000;,
    -0.866026; -0.499999; 0.000000;,
    -0.000523; -0.000302; 1.000000;,
    -0.000523; -0.000302; 1.000000;,
    -0.000523; -0.000302; 1.000000;,
    0.000523; 0.000302; 1.000000;,
    0.000523; 0.000302; 1.000000;,
    0.000523; 0.000302; 1.000000;,
    0.000523; 0.000302; 1.000000;,
    0.000523; 0.000302; 1.000000;,
    0.000523; 0.000302; 1.000000;,
    0.000000; 0.000604; 1.000000;,
    0.000000; 0.000604; 1.000000;,
    0.000000; 0.000604; 1.000000;,
    -0.000523; 0.000302; 1.000000;,
    -0.000523; 0.000302; 1.000000;,
    -0.000523; 0.000302; 1.000000;,
    -0.000523; -0.000302; 1.000000;,
    -0.000523; -0.000302; 1.000000;,
    -0.000523; -0.000302; 1.000000;,
    -0.000001; 0.960730; -0.277485;,
    -0.000001; 0.960730; -0.277485;,
    -0.000001; 0.960730; -0.277485;,
    -0.000001; 0.960730; -0.277485;,
    0.000000; 0.960730; -0.277486;,
    0.000000; 0.960730; -0.277486;,
    0.000000; 0.960730; -0.277486;,
    0.000000; 0.960730; -0.277486;,
    0.000001; 0.960730; -0.277485;,
    0.000001; 0.960730; -0.277485;,
    0.000001; 0.960730; -0.277485;,
    0.000001; 0.960730; -0.277485;,
    0.000001; 0.960731; -0.277483;,
    0.000001; 0.960731; -0.277483;,
    0.000001; 0.960731; -0.277483;,
    0.000001; 0.960731; -0.277483;,
    -0.000001; 0.960731; -0.277483;,
    -0.000001; 0.960731; -0.277483;,
    -0.000001; 0.960731; -0.277483;,
    -0.000001; 0.960731; -0.277483;,
    0.587785; -0.224489; -0.777247;,
    0.587785; -0.224489; -0.777247;,
    0.587785; -0.224489; -0.777247;,
    0.587785; -0.224489; -0.777247;,
    -0.587784; -0.224489; -0.777248;,
    -0.587784; -0.224489; -0.777248;,
    -0.587784; -0.224489; -0.777248;,
    -0.587784; -0.224489; -0.777248;,
    -0.951057; 0.085748; 0.296882;,
    -0.951057; 0.085748; 0.296882;,
    -0.951057; 0.085748; 0.296882;,
    -0.951057; 0.085748; 0.296882;,
    0.000000; 0.277486; 0.960730;,
    0.000000; 0.277486; 0.960730;,
    0.000000; 0.277486; 0.960730;,
    0.000000; 0.277486; 0.960730;,
    0.951056; 0.085747; 0.296882;,
    0.951056; 0.085747; 0.296882;,
    0.951056; 0.085747; 0.296882;,
    0.951056; 0.085747; 0.296882;,
    0.000001; 0.960730; -0.277485;,
    0.000001; 0.960730; -0.277485;,
    0.000001; 0.960730; -0.277485;,
    -0.000001; 0.960730; -0.277485;,
    -0.000001; 0.960730; -0.277485;,
    -0.000001; 0.960730; -0.277485;,
    -0.000001; 0.960730; -0.277484;,
    -0.000001; 0.960730; -0.277484;,
    -0.000001; 0.960730; -0.277484;,
    0.000000; 0.960730; -0.277484;,
    0.000000; 0.960730; -0.277484;,
    0.000000; 0.960730; -0.277484;,
    0.000001; 0.960730; -0.277484;,
    0.000001; 0.960730; -0.277484;,
    0.000001; 0.960730; -0.277484;;
43;
4; 0, 3, 2, 1;,
4; 4, 7, 6, 5;,
4; 8, 11, 10, 9;,
4; 12, 15, 14, 13;,
4; 16, 19, 18, 17;,
3; 20, 22, 21;,
3; 23, 25, 24;,
3; 26, 28, 27;,
3; 29, 31, 30;,
3; 32, 34, 33;,
3; 35, 37, 36;,
3; 38, 40, 39;,
3; 41, 43, 42;,
3; 44, 46, 45;,
3; 47, 49, 48;,
3; 50, 52, 51;,
4; 53, 56, 55, 54;,
4; 57, 60, 59, 58;,
4; 61, 64, 63, 62;,
4; 65, 68, 67, 66;,
4; 69, 72, 71, 70;,
4; 73, 76, 75, 74;,
3; 77, 79, 78;,
3; 80, 82, 81;,
3; 83, 85, 84;,
3; 86, 88, 87;,
3; 89, 91, 90;,
3; 92, 94, 93;,
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
3; 135, 137, 136;,
3; 138, 140, 139;,
3; 141, 143, 142;,
3; 144, 146, 145;,
3; 147, 149, 148;;
}  //End of MeshNormals
 }
}
}