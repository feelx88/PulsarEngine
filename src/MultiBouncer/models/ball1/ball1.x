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
    0.000000,-0.000000,-1.000000,0.000000,
    0.000000,1.000000,-0.000000,0.000000,
    0.000000,0.000000,0.000000,1.000000;;
  }
  Frame Sphere {

    FrameTransformMatrix {
      1.000000,0.000000,0.000000,0.000000,
      0.000000,1.000000,0.000000,0.000000,
      0.000000,0.000000,1.000000,0.000000,
      0.000000,0.000000,0.000000,1.000000;;
    }
Mesh {
240;
-0.000000; -0.000000; -0.500000;,
0.135300; 0.135300; -0.461900;,
0.191300; 0.000000; -0.461900;,
0.191300; 0.000000; -0.461900;,
0.135300; 0.135300; -0.461900;,
0.250000; 0.250000; -0.353600;,
0.353600; 0.000000; -0.353600;,
0.353600; 0.000000; -0.353600;,
0.250000; 0.250000; -0.353600;,
0.326600; 0.326600; -0.191300;,
0.461900; 0.000000; -0.191300;,
0.461900; 0.000000; -0.191300;,
0.326600; 0.326600; -0.191300;,
0.353600; 0.353600; 0.000000;,
0.500000; 0.000000; -0.000000;,
0.500000; 0.000000; -0.000000;,
0.353600; 0.353600; 0.000000;,
0.326600; 0.326600; 0.191300;,
0.461900; 0.000000; 0.191300;,
0.461900; 0.000000; 0.191300;,
0.326600; 0.326600; 0.191300;,
0.250000; 0.250000; 0.353600;,
0.353600; 0.000000; 0.353600;,
0.353600; 0.000000; 0.353600;,
0.250000; 0.250000; 0.353600;,
0.135300; 0.135300; 0.461900;,
0.191300; 0.000000; 0.461900;,
0.135300; 0.135300; 0.461900;,
0.000000; 0.000000; 0.500000;,
0.191300; 0.000000; 0.461900;,
-0.000000; 0.191300; 0.461900;,
0.000000; 0.000000; 0.500000;,
0.135300; 0.135300; 0.461900;,
0.250000; 0.250000; 0.353600;,
-0.000000; 0.353600; 0.353600;,
-0.000000; 0.191300; 0.461900;,
0.135300; 0.135300; 0.461900;,
0.326600; 0.326600; 0.191300;,
-0.000000; 0.461900; 0.191300;,
-0.000000; 0.353600; 0.353600;,
0.250000; 0.250000; 0.353600;,
0.353600; 0.353600; 0.000000;,
-0.000000; 0.500000; 0.000000;,
-0.000000; 0.461900; 0.191300;,
0.326600; 0.326600; 0.191300;,
0.326600; 0.326600; -0.191300;,
-0.000000; 0.461900; -0.191300;,
-0.000000; 0.500000; 0.000000;,
0.353600; 0.353600; 0.000000;,
0.250000; 0.250000; -0.353600;,
-0.000000; 0.353600; -0.353600;,
-0.000000; 0.461900; -0.191300;,
0.326600; 0.326600; -0.191300;,
0.135300; 0.135300; -0.461900;,
-0.000000; 0.191300; -0.461900;,
-0.000000; 0.353600; -0.353600;,
0.250000; 0.250000; -0.353600;,
-0.000000; -0.000000; -0.500000;,
-0.000000; 0.191300; -0.461900;,
0.135300; 0.135300; -0.461900;,
-0.000000; -0.000000; -0.500000;,
-0.135300; 0.135300; -0.461900;,
-0.000000; 0.191300; -0.461900;,
-0.000000; 0.191300; -0.461900;,
-0.135300; 0.135300; -0.461900;,
-0.250000; 0.250000; -0.353600;,
-0.000000; 0.353600; -0.353600;,
-0.000000; 0.353600; -0.353600;,
-0.250000; 0.250000; -0.353600;,
-0.326600; 0.326600; -0.191300;,
-0.000000; 0.461900; -0.191300;,
-0.000000; 0.461900; -0.191300;,
-0.326600; 0.326600; -0.191300;,
-0.353600; 0.353600; 0.000000;,
-0.000000; 0.500000; 0.000000;,
-0.000000; 0.500000; 0.000000;,
-0.353600; 0.353600; 0.000000;,
-0.326600; 0.326600; 0.191300;,
-0.000000; 0.461900; 0.191300;,
-0.000000; 0.461900; 0.191300;,
-0.326600; 0.326600; 0.191300;,
-0.250000; 0.250000; 0.353600;,
-0.000000; 0.353600; 0.353600;,
-0.000000; 0.353600; 0.353600;,
-0.250000; 0.250000; 0.353600;,
-0.135300; 0.135300; 0.461900;,
-0.000000; 0.191300; 0.461900;,
-0.135300; 0.135300; 0.461900;,
0.000000; 0.000000; 0.500000;,
-0.000000; 0.191300; 0.461900;,
-0.191300; -0.000000; 0.461900;,
0.000000; 0.000000; 0.500000;,
-0.135300; 0.135300; 0.461900;,
-0.250000; 0.250000; 0.353600;,
-0.353600; -0.000000; 0.353600;,
-0.191300; -0.000000; 0.461900;,
-0.135300; 0.135300; 0.461900;,
-0.326600; 0.326600; 0.191300;,
-0.461900; -0.000000; 0.191300;,
-0.353600; -0.000000; 0.353600;,
-0.250000; 0.250000; 0.353600;,
-0.353600; 0.353600; 0.000000;,
-0.500000; -0.000000; 0.000000;,
-0.461900; -0.000000; 0.191300;,
-0.326600; 0.326600; 0.191300;,
-0.326600; 0.326600; -0.191300;,
-0.461900; -0.000000; -0.191300;,
-0.500000; -0.000000; 0.000000;,
-0.353600; 0.353600; 0.000000;,
-0.250000; 0.250000; -0.353600;,
-0.353600; -0.000000; -0.353600;,
-0.461900; -0.000000; -0.191300;,
-0.326600; 0.326600; -0.191300;,
-0.135300; 0.135300; -0.461900;,
-0.191300; -0.000000; -0.461900;,
-0.353600; -0.000000; -0.353600;,
-0.250000; 0.250000; -0.353600;,
-0.000000; -0.000000; -0.500000;,
-0.191300; -0.000000; -0.461900;,
-0.135300; 0.135300; -0.461900;,
-0.000000; -0.000000; -0.500000;,
-0.135300; -0.135300; -0.461900;,
-0.191300; -0.000000; -0.461900;,
-0.191300; -0.000000; -0.461900;,
-0.135300; -0.135300; -0.461900;,
-0.250000; -0.250000; -0.353600;,
-0.353600; -0.000000; -0.353600;,
-0.353600; -0.000000; -0.353600;,
-0.250000; -0.250000; -0.353600;,
-0.326600; -0.326600; -0.191300;,
-0.461900; -0.000000; -0.191300;,
-0.461900; -0.000000; -0.191300;,
-0.326600; -0.326600; -0.191300;,
-0.353600; -0.353600; 0.000000;,
-0.500000; -0.000000; 0.000000;,
-0.500000; -0.000000; 0.000000;,
-0.353600; -0.353600; 0.000000;,
-0.326600; -0.326600; 0.191300;,
-0.461900; -0.000000; 0.191300;,
-0.461900; -0.000000; 0.191300;,
-0.326600; -0.326600; 0.191300;,
-0.250000; -0.250000; 0.353600;,
-0.353600; -0.000000; 0.353600;,
-0.353600; -0.000000; 0.353600;,
-0.250000; -0.250000; 0.353600;,
-0.135300; -0.135300; 0.461900;,
-0.191300; -0.000000; 0.461900;,
-0.135300; -0.135300; 0.461900;,
0.000000; 0.000000; 0.500000;,
-0.191300; -0.000000; 0.461900;,
0.000000; -0.191300; 0.461900;,
0.000000; 0.000000; 0.500000;,
-0.135300; -0.135300; 0.461900;,
-0.250000; -0.250000; 0.353600;,
0.000000; -0.353600; 0.353600;,
0.000000; -0.191300; 0.461900;,
-0.135300; -0.135300; 0.461900;,
-0.326600; -0.326600; 0.191300;,
0.000000; -0.461900; 0.191300;,
0.000000; -0.353600; 0.353600;,
-0.250000; -0.250000; 0.353600;,
-0.353600; -0.353600; 0.000000;,
0.000000; -0.500000; 0.000000;,
0.000000; -0.461900; 0.191300;,
-0.326600; -0.326600; 0.191300;,
-0.326600; -0.326600; -0.191300;,
0.000000; -0.461900; -0.191300;,
0.000000; -0.500000; 0.000000;,
-0.353600; -0.353600; 0.000000;,
-0.250000; -0.250000; -0.353600;,
0.000000; -0.353600; -0.353600;,
0.000000; -0.461900; -0.191300;,
-0.326600; -0.326600; -0.191300;,
-0.135300; -0.135300; -0.461900;,
0.000000; -0.191300; -0.461900;,
0.000000; -0.353600; -0.353600;,
-0.250000; -0.250000; -0.353600;,
-0.000000; -0.000000; -0.500000;,
0.000000; -0.191300; -0.461900;,
-0.135300; -0.135300; -0.461900;,
-0.000000; -0.000000; -0.500000;,
0.135300; -0.135300; -0.461900;,
0.000000; -0.191300; -0.461900;,
0.000000; -0.191300; -0.461900;,
0.135300; -0.135300; -0.461900;,
0.250000; -0.250000; -0.353600;,
0.000000; -0.353600; -0.353600;,
0.000000; -0.353600; -0.353600;,
0.250000; -0.250000; -0.353600;,
0.326600; -0.326600; -0.191300;,
0.000000; -0.461900; -0.191300;,
0.000000; -0.461900; -0.191300;,
0.326600; -0.326600; -0.191300;,
0.353600; -0.353600; 0.000000;,
0.000000; -0.500000; 0.000000;,
0.000000; -0.500000; 0.000000;,
0.353600; -0.353600; 0.000000;,
0.326600; -0.326600; 0.191300;,
0.000000; -0.461900; 0.191300;,
0.000000; -0.461900; 0.191300;,
0.326600; -0.326600; 0.191300;,
0.250000; -0.250000; 0.353600;,
0.000000; -0.353600; 0.353600;,
0.000000; -0.353600; 0.353600;,
0.250000; -0.250000; 0.353600;,
0.135300; -0.135300; 0.461900;,
0.000000; -0.191300; 0.461900;,
0.135300; -0.135300; 0.461900;,
0.000000; 0.000000; 0.500000;,
0.000000; -0.191300; 0.461900;,
0.191300; 0.000000; 0.461900;,
0.000000; 0.000000; 0.500000;,
0.135300; -0.135300; 0.461900;,
0.250000; -0.250000; 0.353600;,
0.353600; 0.000000; 0.353600;,
0.191300; 0.000000; 0.461900;,
0.135300; -0.135300; 0.461900;,
0.326600; -0.326600; 0.191300;,
0.461900; 0.000000; 0.191300;,
0.353600; 0.000000; 0.353600;,
0.250000; -0.250000; 0.353600;,
0.353600; -0.353600; 0.000000;,
0.500000; 0.000000; -0.000000;,
0.461900; 0.000000; 0.191300;,
0.326600; -0.326600; 0.191300;,
0.326600; -0.326600; -0.191300;,
0.461900; 0.000000; -0.191300;,
0.500000; 0.000000; -0.000000;,
0.353600; -0.353600; 0.000000;,
0.250000; -0.250000; -0.353600;,
0.353600; 0.000000; -0.353600;,
0.461900; 0.000000; -0.191300;,
0.326600; -0.326600; -0.191300;,
0.135300; -0.135300; -0.461900;,
0.191300; 0.000000; -0.461900;,
0.353600; 0.000000; -0.353600;,
0.250000; -0.250000; -0.353600;,
-0.000000; -0.000000; -0.500000;,
0.191300; 0.000000; -0.461900;,
0.135300; -0.135300; -0.461900;;
64;
3; 0, 1, 2;,
4; 3, 4, 5, 6;,
4; 7, 8, 9, 10;,
4; 11, 12, 13, 14;,
4; 15, 16, 17, 18;,
4; 19, 20, 21, 22;,
4; 23, 24, 25, 26;,
3; 27, 28, 29;,
3; 30, 31, 32;,
4; 33, 34, 35, 36;,
4; 37, 38, 39, 40;,
4; 41, 42, 43, 44;,
4; 45, 46, 47, 48;,
4; 49, 50, 51, 52;,
4; 53, 54, 55, 56;,
3; 57, 58, 59;,
3; 60, 61, 62;,
4; 63, 64, 65, 66;,
4; 67, 68, 69, 70;,
4; 71, 72, 73, 74;,
4; 75, 76, 77, 78;,
4; 79, 80, 81, 82;,
4; 83, 84, 85, 86;,
3; 87, 88, 89;,
3; 90, 91, 92;,
4; 93, 94, 95, 96;,
4; 97, 98, 99, 100;,
4; 101, 102, 103, 104;,
4; 105, 106, 107, 108;,
4; 109, 110, 111, 112;,
4; 113, 114, 115, 116;,
3; 117, 118, 119;,
3; 120, 121, 122;,
4; 123, 124, 125, 126;,
4; 127, 128, 129, 130;,
4; 131, 132, 133, 134;,
4; 135, 136, 137, 138;,
4; 139, 140, 141, 142;,
4; 143, 144, 145, 146;,
3; 147, 148, 149;,
3; 150, 151, 152;,
4; 153, 154, 155, 156;,
4; 157, 158, 159, 160;,
4; 161, 162, 163, 164;,
4; 165, 166, 167, 168;,
4; 169, 170, 171, 172;,
4; 173, 174, 175, 176;,
3; 177, 178, 179;,
3; 180, 181, 182;,
4; 183, 184, 185, 186;,
4; 187, 188, 189, 190;,
4; 191, 192, 193, 194;,
4; 195, 196, 197, 198;,
4; 199, 200, 201, 202;,
4; 203, 204, 205, 206;,
3; 207, 208, 209;,
3; 210, 211, 212;,
4; 213, 214, 215, 216;,
4; 217, 218, 219, 220;,
4; 221, 222, 223, 224;,
4; 225, 226, 227, 228;,
4; 229, 230, 231, 232;,
4; 233, 234, 235, 236;,
3; 237, 238, 239;;
  MeshMaterialList {
    2;
    64;
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1;;
  Material Material_004 {
    0.000000; 0.000000; 0.000000;1.0;;
    0.500000;
    0.500000; 0.500000; 0.500000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
  Material Mat1 {
    1.0; 1.0; 1.0; 1.0;;
    1.0;
    1.0; 1.0; 1.0;;
    0.0; 0.0; 0.0;;
  TextureFilename {    "ball1.png";  }
  }  // End of Material
    }  //End of MeshMaterialList
  MeshNormals {
240;
    0.000000; -0.000000; -1.000000;,
    0.269132; 0.269132; -0.924735;,
    0.380611; 0.000000; -0.924735;,
    0.380611; 0.000000; -0.924735;,
    0.269132; 0.269132; -0.924735;,
    0.498494; 0.498494; -0.709230;,
    0.704977; 0.000000; -0.709230;,
    0.704977; 0.000000; -0.709230;,
    0.498494; 0.498494; -0.709230;,
    0.652733; 0.652733; -0.384551;,
    0.923104; 0.000000; -0.384551;,
    0.923104; 0.000000; -0.384551;,
    0.652733; 0.652733; -0.384551;,
    0.707107; 0.707107; -0.000000;,
    1.000000; 0.000000; -0.000000;,
    1.000000; 0.000000; -0.000000;,
    0.707107; 0.707107; -0.000000;,
    0.652733; 0.652733; 0.384551;,
    0.923104; 0.000000; 0.384551;,
    0.923104; 0.000000; 0.384551;,
    0.652733; 0.652733; 0.384551;,
    0.498494; 0.498494; 0.709230;,
    0.704977; 0.000000; 0.709230;,
    0.704977; 0.000000; 0.709230;,
    0.498494; 0.498494; 0.709230;,
    0.269132; 0.269133; 0.924735;,
    0.380611; 0.000000; 0.924735;,
    0.269132; 0.269133; 0.924735;,
    0.000000; 0.000000; 1.000000;,
    0.380611; 0.000000; 0.924735;,
    -0.000000; 0.380611; 0.924735;,
    0.000000; 0.000000; 1.000000;,
    0.269132; 0.269133; 0.924735;,
    0.498494; 0.498494; 0.709230;,
    -0.000000; 0.704977; 0.709230;,
    -0.000000; 0.380611; 0.924735;,
    0.269132; 0.269133; 0.924735;,
    0.652733; 0.652733; 0.384551;,
    -0.000000; 0.923104; 0.384551;,
    -0.000000; 0.704977; 0.709230;,
    0.498494; 0.498494; 0.709230;,
    0.707107; 0.707107; -0.000000;,
    -0.000000; 1.000000; -0.000000;,
    -0.000000; 0.923104; 0.384551;,
    0.652733; 0.652733; 0.384551;,
    0.652733; 0.652733; -0.384551;,
    -0.000000; 0.923104; -0.384551;,
    -0.000000; 1.000000; -0.000000;,
    0.707107; 0.707107; -0.000000;,
    0.498494; 0.498494; -0.709230;,
    -0.000000; 0.704977; -0.709230;,
    -0.000000; 0.923104; -0.384551;,
    0.652733; 0.652733; -0.384551;,
    0.269132; 0.269132; -0.924735;,
    -0.000000; 0.380611; -0.924735;,
    -0.000000; 0.704977; -0.709230;,
    0.498494; 0.498494; -0.709230;,
    0.000000; -0.000000; -1.000000;,
    -0.000000; 0.380611; -0.924735;,
    0.269132; 0.269132; -0.924735;,
    0.000000; -0.000000; -1.000000;,
    -0.269132; 0.269132; -0.924735;,
    -0.000000; 0.380611; -0.924735;,
    -0.000000; 0.380611; -0.924735;,
    -0.269132; 0.269132; -0.924735;,
    -0.498494; 0.498494; -0.709230;,
    -0.000000; 0.704977; -0.709230;,
    -0.000000; 0.704977; -0.709230;,
    -0.498494; 0.498494; -0.709230;,
    -0.652733; 0.652733; -0.384551;,
    -0.000000; 0.923104; -0.384551;,
    -0.000000; 0.923104; -0.384551;,
    -0.652733; 0.652733; -0.384551;,
    -0.707107; 0.707107; 0.000000;,
    -0.000000; 1.000000; -0.000000;,
    -0.000000; 1.000000; -0.000000;,
    -0.707107; 0.707107; 0.000000;,
    -0.652733; 0.652733; 0.384551;,
    -0.000000; 0.923104; 0.384551;,
    -0.000000; 0.923104; 0.384551;,
    -0.652733; 0.652733; 0.384551;,
    -0.498494; 0.498494; 0.709230;,
    -0.000000; 0.704977; 0.709230;,
    -0.000000; 0.704977; 0.709230;,
    -0.498494; 0.498494; 0.709230;,
    -0.269133; 0.269132; 0.924735;,
    -0.000000; 0.380611; 0.924735;,
    -0.269133; 0.269132; 0.924735;,
    0.000000; 0.000000; 1.000000;,
    -0.000000; 0.380611; 0.924735;,
    -0.380611; -0.000000; 0.924735;,
    0.000000; 0.000000; 1.000000;,
    -0.269133; 0.269132; 0.924735;,
    -0.498494; 0.498494; 0.709230;,
    -0.704977; -0.000000; 0.709230;,
    -0.380611; -0.000000; 0.924735;,
    -0.269133; 0.269132; 0.924735;,
    -0.652733; 0.652733; 0.384551;,
    -0.923104; -0.000000; 0.384551;,
    -0.704977; -0.000000; 0.709230;,
    -0.498494; 0.498494; 0.709230;,
    -0.707107; 0.707107; 0.000000;,
    -1.000000; -0.000000; 0.000000;,
    -0.923104; -0.000000; 0.384551;,
    -0.652733; 0.652733; 0.384551;,
    -0.652733; 0.652733; -0.384551;,
    -0.923104; -0.000000; -0.384551;,
    -1.000000; -0.000000; 0.000000;,
    -0.707107; 0.707107; 0.000000;,
    -0.498494; 0.498494; -0.709230;,
    -0.704977; -0.000000; -0.709230;,
    -0.923104; -0.000000; -0.384551;,
    -0.652733; 0.652733; -0.384551;,
    -0.269132; 0.269132; -0.924735;,
    -0.380611; -0.000000; -0.924735;,
    -0.704977; -0.000000; -0.709230;,
    -0.498494; 0.498494; -0.709230;,
    0.000000; -0.000000; -1.000000;,
    -0.380611; -0.000000; -0.924735;,
    -0.269132; 0.269132; -0.924735;,
    0.000000; -0.000000; -1.000000;,
    -0.269132; -0.269132; -0.924735;,
    -0.380611; -0.000000; -0.924735;,
    -0.380611; -0.000000; -0.924735;,
    -0.269132; -0.269132; -0.924735;,
    -0.498494; -0.498494; -0.709230;,
    -0.704977; -0.000000; -0.709230;,
    -0.704977; -0.000000; -0.709230;,
    -0.498494; -0.498494; -0.709230;,
    -0.652733; -0.652733; -0.384551;,
    -0.923104; -0.000000; -0.384551;,
    -0.923104; -0.000000; -0.384551;,
    -0.652733; -0.652733; -0.384551;,
    -0.707107; -0.707107; 0.000000;,
    -1.000000; -0.000000; 0.000000;,
    -1.000000; -0.000000; 0.000000;,
    -0.707107; -0.707107; 0.000000;,
    -0.652733; -0.652733; 0.384551;,
    -0.923104; -0.000000; 0.384551;,
    -0.923104; -0.000000; 0.384551;,
    -0.652733; -0.652733; 0.384551;,
    -0.498494; -0.498494; 0.709230;,
    -0.704977; -0.000000; 0.709230;,
    -0.704977; -0.000000; 0.709230;,
    -0.498494; -0.498494; 0.709230;,
    -0.269132; -0.269133; 0.924735;,
    -0.380611; -0.000000; 0.924735;,
    -0.269132; -0.269133; 0.924735;,
    0.000000; 0.000000; 1.000000;,
    -0.380611; -0.000000; 0.924735;,
    0.000000; -0.380611; 0.924735;,
    0.000000; 0.000000; 1.000000;,
    -0.269132; -0.269133; 0.924735;,
    -0.498494; -0.498494; 0.709230;,
    0.000000; -0.704977; 0.709230;,
    0.000000; -0.380611; 0.924735;,
    -0.269132; -0.269133; 0.924735;,
    -0.652733; -0.652733; 0.384551;,
    0.000000; -0.923104; 0.384551;,
    0.000000; -0.704977; 0.709230;,
    -0.498494; -0.498494; 0.709230;,
    -0.707107; -0.707107; 0.000000;,
    0.000000; -1.000000; 0.000000;,
    0.000000; -0.923104; 0.384551;,
    -0.652733; -0.652733; 0.384551;,
    -0.652733; -0.652733; -0.384551;,
    0.000000; -0.923104; -0.384551;,
    0.000000; -1.000000; 0.000000;,
    -0.707107; -0.707107; 0.000000;,
    -0.498494; -0.498494; -0.709230;,
    0.000000; -0.704977; -0.709230;,
    0.000000; -0.923104; -0.384551;,
    -0.652733; -0.652733; -0.384551;,
    -0.269132; -0.269132; -0.924735;,
    0.000000; -0.380611; -0.924735;,
    0.000000; -0.704977; -0.709230;,
    -0.498494; -0.498494; -0.709230;,
    0.000000; -0.000000; -1.000000;,
    0.000000; -0.380611; -0.924735;,
    -0.269132; -0.269132; -0.924735;,
    0.000000; -0.000000; -1.000000;,
    0.269133; -0.269132; -0.924735;,
    0.000000; -0.380611; -0.924735;,
    0.000000; -0.380611; -0.924735;,
    0.269133; -0.269132; -0.924735;,
    0.498494; -0.498494; -0.709230;,
    0.000000; -0.704977; -0.709230;,
    0.000000; -0.704977; -0.709230;,
    0.498494; -0.498494; -0.709230;,
    0.652733; -0.652733; -0.384551;,
    0.000000; -0.923104; -0.384551;,
    0.000000; -0.923104; -0.384551;,
    0.652733; -0.652733; -0.384551;,
    0.707107; -0.707107; 0.000000;,
    0.000000; -1.000000; 0.000000;,
    0.000000; -1.000000; 0.000000;,
    0.707107; -0.707107; 0.000000;,
    0.652733; -0.652733; 0.384551;,
    0.000000; -0.923104; 0.384551;,
    0.000000; -0.923104; 0.384551;,
    0.652733; -0.652733; 0.384551;,
    0.498494; -0.498494; 0.709230;,
    0.000000; -0.704977; 0.709230;,
    0.000000; -0.704977; 0.709230;,
    0.498494; -0.498494; 0.709230;,
    0.269133; -0.269132; 0.924735;,
    0.000000; -0.380611; 0.924735;,
    0.269133; -0.269132; 0.924735;,
    0.000000; 0.000000; 1.000000;,
    0.000000; -0.380611; 0.924735;,
    0.380611; 0.000000; 0.924735;,
    0.000000; 0.000000; 1.000000;,
    0.269133; -0.269132; 0.924735;,
    0.498494; -0.498494; 0.709230;,
    0.704977; 0.000000; 0.709230;,
    0.380611; 0.000000; 0.924735;,
    0.269133; -0.269132; 0.924735;,
    0.652733; -0.652733; 0.384551;,
    0.923104; 0.000000; 0.384551;,
    0.704977; 0.000000; 0.709230;,
    0.498494; -0.498494; 0.709230;,
    0.707107; -0.707107; 0.000000;,
    1.000000; 0.000000; -0.000000;,
    0.923104; 0.000000; 0.384551;,
    0.652733; -0.652733; 0.384551;,
    0.652733; -0.652733; -0.384551;,
    0.923104; 0.000000; -0.384551;,
    1.000000; 0.000000; -0.000000;,
    0.707107; -0.707107; 0.000000;,
    0.498494; -0.498494; -0.709230;,
    0.704977; 0.000000; -0.709230;,
    0.923104; 0.000000; -0.384551;,
    0.652733; -0.652733; -0.384551;,
    0.269133; -0.269132; -0.924735;,
    0.380611; 0.000000; -0.924735;,
    0.704977; 0.000000; -0.709230;,
    0.498494; -0.498494; -0.709230;,
    0.000000; -0.000000; -1.000000;,
    0.380611; 0.000000; -0.924735;,
    0.269133; -0.269132; -0.924735;;
64;
3; 0, 1, 2;,
4; 3, 4, 5, 6;,
4; 7, 8, 9, 10;,
4; 11, 12, 13, 14;,
4; 15, 16, 17, 18;,
4; 19, 20, 21, 22;,
4; 23, 24, 25, 26;,
3; 27, 28, 29;,
3; 30, 31, 32;,
4; 33, 34, 35, 36;,
4; 37, 38, 39, 40;,
4; 41, 42, 43, 44;,
4; 45, 46, 47, 48;,
4; 49, 50, 51, 52;,
4; 53, 54, 55, 56;,
3; 57, 58, 59;,
3; 60, 61, 62;,
4; 63, 64, 65, 66;,
4; 67, 68, 69, 70;,
4; 71, 72, 73, 74;,
4; 75, 76, 77, 78;,
4; 79, 80, 81, 82;,
4; 83, 84, 85, 86;,
3; 87, 88, 89;,
3; 90, 91, 92;,
4; 93, 94, 95, 96;,
4; 97, 98, 99, 100;,
4; 101, 102, 103, 104;,
4; 105, 106, 107, 108;,
4; 109, 110, 111, 112;,
4; 113, 114, 115, 116;,
3; 117, 118, 119;,
3; 120, 121, 122;,
4; 123, 124, 125, 126;,
4; 127, 128, 129, 130;,
4; 131, 132, 133, 134;,
4; 135, 136, 137, 138;,
4; 139, 140, 141, 142;,
4; 143, 144, 145, 146;,
3; 147, 148, 149;,
3; 150, 151, 152;,
4; 153, 154, 155, 156;,
4; 157, 158, 159, 160;,
4; 161, 162, 163, 164;,
4; 165, 166, 167, 168;,
4; 169, 170, 171, 172;,
4; 173, 174, 175, 176;,
3; 177, 178, 179;,
3; 180, 181, 182;,
4; 183, 184, 185, 186;,
4; 187, 188, 189, 190;,
4; 191, 192, 193, 194;,
4; 195, 196, 197, 198;,
4; 199, 200, 201, 202;,
4; 203, 204, 205, 206;,
3; 207, 208, 209;,
3; 210, 211, 212;,
4; 213, 214, 215, 216;,
4; 217, 218, 219, 220;,
4; 221, 222, 223, 224;,
4; 225, 226, 227, 228;,
4; 229, 230, 231, 232;,
4; 233, 234, 235, 236;,
3; 237, 238, 239;;
}  //End of MeshNormals
MeshTextureCoords {
240;
0.572491;-0.955815;,
0.554081;-0.831205;,
0.649010;-0.837358;,
0.649010;-0.837358;,
0.554081;-0.831205;,
0.550892;-0.706272;,
0.662022;-0.713427;,
0.662022;-0.713427;,
0.550892;-0.706272;,
0.549226;-0.581308;,
0.668637;-0.588970;,
0.668637;-0.588970;,
0.549226;-0.581308;,
0.547885;-0.456336;,
0.673852;-0.464397;,
0.673852;-0.464397;,
0.547885;-0.456336;,
0.546381;-0.331368;,
0.679574;-0.339865;,
0.679574;-0.339865;,
0.546381;-0.331368;,
0.543914;-0.206420;,
0.688648;-0.215610;,
0.688648;-0.215610;,
0.543914;-0.206420;,
0.535516;-0.081597;,
0.716405;-0.092905;,
0.535516;-0.081597;,
1.072491;-0.044185;,
0.716405;-0.092905;,
0.370543;-0.104804;,
0.072491;-0.044185;,
0.535516;-0.081597;,
0.543914;-0.206420;,
0.403010;-0.226116;,
0.370543;-0.104804;,
0.535516;-0.081597;,
0.546381;-0.331368;,
0.414725;-0.349801;,
0.403010;-0.226116;,
0.543914;-0.206420;,
0.547885;-0.456336;,
0.422385;-0.473943;,
0.414725;-0.349801;,
0.546381;-0.331368;,
0.549226;-0.581308;,
0.429546;-0.598141;,
0.422385;-0.473943;,
0.547885;-0.456336;,
0.550892;-0.706272;,
0.438862;-0.722097;,
0.429546;-0.598141;,
0.549226;-0.581308;,
0.554081;-0.831205;,
0.457862;-0.844956;,
0.438862;-0.722097;,
0.550892;-0.706272;,
0.572491;-0.955815;,
0.457862;-0.844956;,
0.554081;-0.831205;,
0.572491;-0.955815;,
0.351626;-0.874329;,
0.457862;-0.844956;,
0.457862;-0.844956;,
0.351626;-0.874329;,
0.320444;-0.753678;,
0.438862;-0.722097;,
0.438862;-0.722097;,
0.320444;-0.753678;,
0.307436;-0.630470;,
0.429546;-0.598141;,
0.429546;-0.598141;,
0.307436;-0.630470;,
0.298348;-0.506719;,
0.422385;-0.473943;,
0.422385;-0.473943;,
0.298348;-0.506719;,
0.289417;-0.382946;,
0.414725;-0.349801;,
0.414725;-0.349801;,
0.289417;-0.382946;,
0.277147;-0.259636;,
0.403010;-0.226116;,
0.403010;-0.226116;,
0.277147;-0.259636;,
0.249867;-0.138430;,
0.370543;-0.104804;,
0.249867;-0.138430;,
0.072491;-0.044185;,
0.370543;-0.104804;,
0.149010;-0.162642;,
0.072491;-0.044185;,
0.249867;-0.138430;,
0.277147;-0.259636;,
0.162022;-0.286573;,
0.149010;-0.162642;,
0.249867;-0.138430;,
0.289417;-0.382946;,
0.168637;-0.411031;,
0.162022;-0.286573;,
0.277147;-0.259636;,
0.298348;-0.506719;,
0.173852;-0.535603;,
0.168637;-0.411031;,
0.289417;-0.382946;,
0.307436;-0.630470;,
0.179574;-0.660135;,
0.173852;-0.535603;,
0.298348;-0.506719;,
0.320444;-0.753678;,
0.188648;-0.784390;,
0.179574;-0.660135;,
0.307436;-0.630470;,
0.351626;-0.874329;,
0.216405;-0.907095;,
0.188648;-0.784390;,
0.320444;-0.753678;,
0.572491;-0.955815;,
0.216405;-0.907095;,
0.351626;-0.874329;,
0.572491;-0.955815;,
1.035516;-0.918403;,
0.216405;-0.907095;,
0.216405;-0.907095;,
0.035516;-0.918403;,
0.043914;-0.793580;,
0.188648;-0.784390;,
0.188648;-0.784390;,
0.043914;-0.793580;,
0.046381;-0.668632;,
0.179574;-0.660135;,
0.179574;-0.660135;,
0.046381;-0.668632;,
0.047885;-0.543664;,
0.173852;-0.535603;,
0.173852;-0.535603;,
0.047885;-0.543664;,
0.049226;-0.418692;,
0.168637;-0.411031;,
0.168637;-0.411031;,
0.049226;-0.418692;,
0.050892;-0.293728;,
0.162022;-0.286573;,
0.162022;-0.286573;,
0.050892;-0.293728;,
0.054081;-0.168795;,
0.149010;-0.162642;,
0.054081;-0.168795;,
0.072491;-0.044185;,
0.149010;-0.162642;,
0.957862;-0.155044;,
1.072491;-0.044185;,
1.054081;-0.168795;,
1.050892;-0.293728;,
0.938862;-0.277903;,
0.957862;-0.155044;,
1.054081;-0.168795;,
1.049226;-0.418692;,
0.929546;-0.401859;,
0.938862;-0.277903;,
1.050892;-0.293728;,
1.047885;-0.543664;,
0.922385;-0.526057;,
0.929546;-0.401859;,
1.049226;-0.418692;,
1.046381;-0.668632;,
0.914725;-0.650199;,
0.922385;-0.526057;,
1.047885;-0.543664;,
1.043914;-0.793580;,
0.903010;-0.773884;,
0.914725;-0.650199;,
1.046381;-0.668632;,
1.035516;-0.918403;,
0.870543;-0.895196;,
0.903010;-0.773884;,
1.043914;-0.793580;,
0.572491;-0.955815;,
0.870543;-0.895196;,
1.035516;-0.918403;,
0.572491;-0.955815;,
0.749867;-0.861570;,
0.870543;-0.895196;,
0.870543;-0.895196;,
0.749867;-0.861570;,
0.777147;-0.740364;,
0.903010;-0.773884;,
0.903010;-0.773884;,
0.777147;-0.740364;,
0.789416;-0.617054;,
0.914725;-0.650199;,
0.914725;-0.650199;,
0.789416;-0.617054;,
0.798348;-0.493281;,
0.922385;-0.526057;,
0.922385;-0.526057;,
0.798348;-0.493281;,
0.807436;-0.369530;,
0.929546;-0.401859;,
0.929546;-0.401859;,
0.807436;-0.369530;,
0.820444;-0.246322;,
0.938862;-0.277903;,
0.938862;-0.277903;,
0.820444;-0.246322;,
0.851626;-0.125671;,
0.957862;-0.155044;,
0.851626;-0.125671;,
1.072491;-0.044185;,
0.957862;-0.155044;,
0.716405;-0.092905;,
1.072491;-0.044185;,
0.851626;-0.125671;,
0.820444;-0.246322;,
0.688648;-0.215610;,
0.716405;-0.092905;,
0.851626;-0.125671;,
0.807436;-0.369530;,
0.679574;-0.339865;,
0.688648;-0.215610;,
0.820444;-0.246322;,
0.798348;-0.493281;,
0.673852;-0.464397;,
0.679574;-0.339865;,
0.807436;-0.369530;,
0.789416;-0.617054;,
0.668637;-0.588970;,
0.673852;-0.464397;,
0.798348;-0.493281;,
0.777147;-0.740364;,
0.662022;-0.713427;,
0.668637;-0.588970;,
0.789416;-0.617054;,
0.749867;-0.861570;,
0.649010;-0.837358;,
0.662022;-0.713427;,
0.777147;-0.740364;,
0.572491;-0.955815;,
0.649010;-0.837358;,
0.749867;-0.861570;;
}  //End of MeshTextureCoords
  }  // End of the Mesh Sphere 
  }  // SI End of the Object Sphere 
}  // End of the Root Frame