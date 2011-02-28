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
  Frame Cube {

    FrameTransformMatrix {
      1.600000,0.000000,0.000000,0.000000,
      0.000000,1.400000,0.000000,0.000000,
      0.000000,0.000000,1.000000,0.000000,
      0.000000,0.000000,0.000000,1.000000;;
    }
Mesh {
24;
25.000000; 25.000000; -0.500000;,
25.000000; -25.000000; -0.500000;,
-25.000000; -25.000000; -0.500000;,
-25.000000; 25.000000; -0.500000;,
25.000000; 25.000000; 0.500000;,
-25.000000; 25.000000; 0.500000;,
-25.000000; -25.000000; 0.500000;,
25.000000; -25.000000; 0.500000;,
25.000000; 25.000000; -0.500000;,
25.000000; 25.000000; 0.500000;,
25.000000; -25.000000; 0.500000;,
25.000000; -25.000000; -0.500000;,
25.000000; -25.000000; -0.500000;,
25.000000; -25.000000; 0.500000;,
-25.000000; -25.000000; 0.500000;,
-25.000000; -25.000000; -0.500000;,
-25.000000; -25.000000; -0.500000;,
-25.000000; -25.000000; 0.500000;,
-25.000000; 25.000000; 0.500000;,
-25.000000; 25.000000; -0.500000;,
25.000000; 25.000000; 0.500000;,
25.000000; 25.000000; -0.500000;,
-25.000000; 25.000000; -0.500000;,
-25.000000; 25.000000; 0.500000;;
6;
4; 0, 1, 2, 3;,
4; 4, 5, 6, 7;,
4; 8, 9, 10, 11;,
4; 12, 13, 14, 15;,
4; 16, 17, 18, 19;,
4; 20, 21, 22, 23;;
  MeshMaterialList {
    2;
    6;
    1,
    1,
    0,
    0,
    0,
    0;;
  Material Material {
    0.800000; 0.800000; 0.800000;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
  Material Mat1 {
    1.0; 1.0; 1.0; 1.0;;
    1.0;
    1.0; 1.0; 1.0;;
    0.0; 0.0; 0.0;;
  TextureFilename {    "floortex1.png";  }
  }  // End of Material
    }  //End of MeshMaterialList
  MeshNormals {
24;
    0.577353; 0.577353; -0.577345;,
    0.577350; -0.577350; -0.577351;,
    -0.577348; -0.577348; -0.577355;,
    -0.577351; 0.577351; -0.577349;,
    0.577348; 0.577348; 0.577355;,
    -0.577349; 0.577350; 0.577352;,
    -0.577353; -0.577352; 0.577346;,
    0.577350; -0.577351; 0.577350;,
    0.577353; 0.577353; -0.577345;,
    0.577348; 0.577348; 0.577355;,
    0.577350; -0.577351; 0.577350;,
    0.577350; -0.577350; -0.577351;,
    0.577350; -0.577350; -0.577351;,
    0.577350; -0.577351; 0.577350;,
    -0.577353; -0.577352; 0.577346;,
    -0.577348; -0.577348; -0.577355;,
    -0.577348; -0.577348; -0.577355;,
    -0.577353; -0.577352; 0.577346;,
    -0.577349; 0.577350; 0.577352;,
    -0.577351; 0.577351; -0.577349;,
    0.577348; 0.577348; 0.577355;,
    0.577353; 0.577353; -0.577345;,
    -0.577351; 0.577351; -0.577349;,
    -0.577349; 0.577350; 0.577352;;
6;
4; 0, 1, 2, 3;,
4; 4, 5, 6, 7;,
4; 8, 9, 10, 11;,
4; 12, 13, 14, 15;,
4; 16, 17, 18, 19;,
4; 20, 21, 22, 23;;
}  //End of MeshNormals
MeshTextureCoords {
24;
1.000000;-1.000000;,
0.000000;-1.000000;,
0.000000;-0.000000;,
1.000000;-0.000000;,
1.000000;-0.999999;,
0.000000;-1.000000;,
0.000000;-0.000000;,
0.999999;-0.000000;,
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
0.000000;-1.000000;;
}  //End of MeshTextureCoords
  }  // End of the Mesh Cube 
  }  // SI End of the Object Cube 
}  // End of the Root Frame