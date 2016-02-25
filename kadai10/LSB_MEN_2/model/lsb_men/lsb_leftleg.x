xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 78;
 0.01201;-0.00290;-0.07424;,
 0.04190;-0.00279;-0.06237;,
 0.04609;-0.81819;-0.06618;,
 0.01620;-0.81828;-0.07805;,
 0.06438;-0.00279;-0.03937;,
 0.06856;-0.81818;-0.04318;,
 0.07556;-0.00287;-0.00922;,
 0.07974;-0.81826;-0.01303;,
 0.07351;-0.00303;0.02288;,
 0.07769;-0.81842;0.01907;,
 0.05858;-0.00324;0.05136;,
 0.06276;-0.81863;0.04755;,
 0.03336;-0.00346;0.07131;,
 0.03754;-0.81885;0.06751;,
 0.00220;-0.00366;0.07928;,
 0.00638;-0.81905;0.07547;,
 -0.02950;-0.00380;0.07388;,
 -0.02532;-0.81919;0.07007;,
 -0.05627;-0.00385;0.05606;,
 -0.05209;-0.81924;0.05225;,
 -0.07347;-0.00382;0.02889;,
 -0.06929;-0.81920;0.02508;,
 -0.07814;-0.00369;-0.00293;,
 -0.07396;-0.81908;-0.00674;,
 -0.06946;-0.00350;-0.03389;,
 -0.06528;-0.81889;-0.03770;,
 -0.04894;-0.00328;-0.05866;,
 -0.04475;-0.81867;-0.06246;,
 -0.02012;-0.00307;-0.07293;,
 -0.01593;-0.81845;-0.07673;,
 0.01201;-0.00290;-0.07424;,
 0.01620;-0.81828;-0.07805;,
 -0.00096;-0.00332;0.00200;,
 -0.00096;-0.00332;0.00200;,
 -0.00096;-0.00332;0.00200;,
 -0.00096;-0.00332;0.00200;,
 -0.00096;-0.00332;0.00200;,
 -0.00096;-0.00332;0.00200;,
 -0.00096;-0.00332;0.00200;,
 -0.00096;-0.00332;0.00200;,
 -0.00096;-0.00332;0.00200;,
 -0.00096;-0.00332;0.00200;,
 -0.00096;-0.00332;0.00200;,
 -0.00096;-0.00332;0.00200;,
 -0.00096;-0.00332;0.00200;,
 -0.00096;-0.00332;0.00200;,
 -0.00096;-0.00332;0.00200;,
 0.00301;-0.81930;0.00034;,
 0.01599;-0.81887;-0.07590;,
 0.04587;-0.81877;-0.06404;,
 0.00301;-0.81930;0.00034;,
 0.06836;-0.81877;-0.04104;,
 0.00301;-0.81930;0.00034;,
 0.07953;-0.81886;-0.01088;,
 0.00301;-0.81930;0.00034;,
 0.07748;-0.81901;0.02121;,
 0.00301;-0.81930;0.00034;,
 0.06255;-0.81922;0.04970;,
 0.00301;-0.81930;0.00034;,
 0.03733;-0.81945;0.06965;,
 0.00301;-0.81930;0.00034;,
 0.00618;-0.81964;0.07761;,
 0.00301;-0.81930;0.00034;,
 -0.02553;-0.81978;0.07221;,
 0.00301;-0.81930;0.00034;,
 -0.05230;-0.81984;0.05439;,
 0.00301;-0.81930;0.00034;,
 -0.06950;-0.81980;0.02722;,
 0.00301;-0.81930;0.00034;,
 -0.07417;-0.81967;-0.00460;,
 0.00301;-0.81930;0.00034;,
 -0.06549;-0.81948;-0.03556;,
 0.00301;-0.81930;0.00034;,
 -0.04496;-0.81926;-0.06032;,
 0.00301;-0.81930;0.00034;,
 -0.01615;-0.81904;-0.07459;,
 0.00301;-0.81930;0.00034;,
 0.01599;-0.81887;-0.07590;;
 
 45;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 3;32,1,0;,
 3;33,4,1;,
 3;34,6,4;,
 3;35,8,6;,
 3;36,10,8;,
 3;37,12,10;,
 3;38,14,12;,
 3;39,16,14;,
 3;40,18,16;,
 3;41,20,18;,
 3;42,22,20;,
 3;43,24,22;,
 3;44,26,24;,
 3;45,28,26;,
 3;46,30,28;,
 3;47,48,49;,
 3;50,49,51;,
 3;52,51,53;,
 3;54,53,55;,
 3;56,55,57;,
 3;58,57,59;,
 3;60,59,61;,
 3;62,61,63;,
 3;64,63,65;,
 3;66,65,67;,
 3;68,67,69;,
 3;70,69,71;,
 3;72,71,73;,
 3;74,73,75;,
 3;76,75,77;;
 
 MeshMaterialList {
  1;
  45;
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
  Material {
   0.029260;0.027500;0.220000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.126350;0.118750;0.950000;;
  }
 }
 MeshNormals {
  47;
  -0.005140;0.999976;0.004665;,
  0.167744;0.005464;-0.985815;,
  0.554221;0.006731;-0.832342;,
  0.844857;0.006834;-0.534949;,
  0.989406;0.005757;-0.145063;,
  0.962887;0.003682;0.269879;,
  0.769880;0.000970;0.638188;,
  0.443722;-0.001908;0.896163;,
  0.040864;-0.004457;0.999155;,
  -0.369067;-0.006234;0.929382;,
  -0.715166;-0.006933;0.698920;,
  -0.937598;-0.006435;0.347661;,
  -0.997953;-0.004824;-0.063767;,
  -0.885732;-0.002379;-0.464191;,
  -0.620381;0.000477;-0.784300;,
  -0.247723;0.003252;-0.968826;,
  0.005120;-0.999976;-0.004680;,
  0.005083;-0.999976;-0.004744;,
  0.005032;-0.999976;-0.004718;,
  0.005096;-0.999976;-0.004622;,
  0.005105;-0.999976;-0.004662;,
  0.005106;-0.999976;-0.004687;,
  0.005120;-0.999976;-0.004688;,
  0.005111;-0.999976;-0.004697;,
  0.005140;-0.999976;-0.004672;,
  0.005173;-0.999976;-0.004676;,
  0.005147;-0.999976;-0.004700;,
  0.005147;-0.999976;-0.004677;,
  0.005161;-0.999976;-0.004687;,
  0.005188;-0.999975;-0.004725;,
  0.005121;-0.999976;-0.004714;,
  0.005123;-0.999976;-0.004690;,
  -0.005176;0.999976;0.004649;,
  -0.005163;0.999976;0.004619;,
  -0.005112;0.999976;0.004691;,
  -0.005115;0.999976;0.004674;,
  -0.005114;0.999976;0.004646;,
  -0.005146;0.999976;0.004676;,
  -0.005162;0.999976;0.004709;,
  -0.005112;0.999976;0.004698;,
  -0.005110;0.999976;0.004686;,
  -0.005156;0.999976;0.004656;,
  -0.005160;0.999976;0.004674;,
  -0.005143;0.999976;0.004651;,
  -0.005166;0.999976;0.004643;,
  -0.005161;0.999976;0.004669;,
  -0.005106;0.999976;0.004638;;
  45;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,1,1,15;,
  3;0,32,33;,
  3;0,34,32;,
  3;0,35,34;,
  3;0,36,35;,
  3;0,37,36;,
  3;0,38,37;,
  3;0,39,38;,
  3;0,40,39;,
  3;0,41,40;,
  3;0,42,41;,
  3;0,43,42;,
  3;0,44,43;,
  3;0,45,44;,
  3;0,46,45;,
  3;0,33,46;,
  3;31,16,17;,
  3;31,17,18;,
  3;31,18,19;,
  3;31,19,20;,
  3;31,20,21;,
  3;31,21,22;,
  3;31,22,23;,
  3;31,23,24;,
  3;31,24,25;,
  3;31,25,26;,
  3;31,26,27;,
  3;31,27,28;,
  3;31,28,29;,
  3;31,29,30;,
  3;31,30,16;;
 }
 MeshTextureCoords {
  78;
  0.000000;0.000000;,
  0.066670;0.000000;,
  0.066670;0.333330;,
  0.000000;0.333330;,
  0.133330;0.000000;,
  0.133330;0.333330;,
  0.200000;0.000000;,
  0.200000;0.333330;,
  0.266670;0.000000;,
  0.266670;0.333330;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.400000;0.000000;,
  0.400000;0.333330;,
  0.466670;0.000000;,
  0.466670;0.333330;,
  0.533330;0.000000;,
  0.533330;0.333330;,
  0.600000;0.000000;,
  0.600000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  0.733330;0.000000;,
  0.733330;0.333330;,
  0.800000;0.000000;,
  0.800000;0.333330;,
  0.866670;0.000000;,
  0.866670;0.333330;,
  0.933330;0.000000;,
  0.933330;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.033330;0.000000;,
  0.100000;0.000000;,
  0.166670;0.000000;,
  0.233330;0.000000;,
  0.300000;0.000000;,
  0.366670;0.000000;,
  0.433330;0.000000;,
  0.500000;0.000000;,
  0.566670;0.000000;,
  0.633330;0.000000;,
  0.700000;0.000000;,
  0.766670;0.000000;,
  0.833330;0.000000;,
  0.900000;0.000000;,
  0.966670;0.000000;,
  0.033330;1.000000;,
  0.000000;1.000000;,
  0.066670;1.000000;,
  0.100000;1.000000;,
  0.133330;1.000000;,
  0.166670;1.000000;,
  0.200000;1.000000;,
  0.233330;1.000000;,
  0.266670;1.000000;,
  0.300000;1.000000;,
  0.333330;1.000000;,
  0.366670;1.000000;,
  0.400000;1.000000;,
  0.433330;1.000000;,
  0.466670;1.000000;,
  0.500000;1.000000;,
  0.533330;1.000000;,
  0.566670;1.000000;,
  0.600000;1.000000;,
  0.633330;1.000000;,
  0.666670;1.000000;,
  0.700000;1.000000;,
  0.733330;1.000000;,
  0.766670;1.000000;,
  0.800000;1.000000;,
  0.833330;1.000000;,
  0.866670;1.000000;,
  0.900000;1.000000;,
  0.933330;1.000000;,
  0.966670;1.000000;,
  1.000000;1.000000;;
 }
 MeshVertexColors {
  78;
  0;1.000000;1.000000;1.000000;1.000000;,
  1;1.000000;1.000000;1.000000;1.000000;,
  2;1.000000;1.000000;1.000000;1.000000;,
  3;1.000000;1.000000;1.000000;1.000000;,
  4;1.000000;1.000000;1.000000;1.000000;,
  5;1.000000;1.000000;1.000000;1.000000;,
  6;1.000000;1.000000;1.000000;1.000000;,
  7;1.000000;1.000000;1.000000;1.000000;,
  8;1.000000;1.000000;1.000000;1.000000;,
  9;1.000000;1.000000;1.000000;1.000000;,
  10;1.000000;1.000000;1.000000;1.000000;,
  11;1.000000;1.000000;1.000000;1.000000;,
  12;1.000000;1.000000;1.000000;1.000000;,
  13;1.000000;1.000000;1.000000;1.000000;,
  14;1.000000;1.000000;1.000000;1.000000;,
  15;1.000000;1.000000;1.000000;1.000000;,
  16;1.000000;1.000000;1.000000;1.000000;,
  17;1.000000;1.000000;1.000000;1.000000;,
  18;1.000000;1.000000;1.000000;1.000000;,
  19;1.000000;1.000000;1.000000;1.000000;,
  20;1.000000;1.000000;1.000000;1.000000;,
  21;1.000000;1.000000;1.000000;1.000000;,
  22;1.000000;1.000000;1.000000;1.000000;,
  23;1.000000;1.000000;1.000000;1.000000;,
  24;1.000000;1.000000;1.000000;1.000000;,
  25;1.000000;1.000000;1.000000;1.000000;,
  26;1.000000;1.000000;1.000000;1.000000;,
  27;1.000000;1.000000;1.000000;1.000000;,
  28;1.000000;1.000000;1.000000;1.000000;,
  29;1.000000;1.000000;1.000000;1.000000;,
  30;1.000000;1.000000;1.000000;1.000000;,
  31;1.000000;1.000000;1.000000;1.000000;,
  32;1.000000;1.000000;1.000000;1.000000;,
  33;1.000000;1.000000;1.000000;1.000000;,
  34;1.000000;1.000000;1.000000;1.000000;,
  35;1.000000;1.000000;1.000000;1.000000;,
  36;1.000000;1.000000;1.000000;1.000000;,
  37;1.000000;1.000000;1.000000;1.000000;,
  38;1.000000;1.000000;1.000000;1.000000;,
  39;1.000000;1.000000;1.000000;1.000000;,
  40;1.000000;1.000000;1.000000;1.000000;,
  41;1.000000;1.000000;1.000000;1.000000;,
  42;1.000000;1.000000;1.000000;1.000000;,
  43;1.000000;1.000000;1.000000;1.000000;,
  44;1.000000;1.000000;1.000000;1.000000;,
  45;1.000000;1.000000;1.000000;1.000000;,
  46;1.000000;1.000000;1.000000;1.000000;,
  47;1.000000;1.000000;1.000000;1.000000;,
  48;1.000000;1.000000;1.000000;1.000000;,
  49;1.000000;1.000000;1.000000;1.000000;,
  50;1.000000;1.000000;1.000000;1.000000;,
  51;1.000000;1.000000;1.000000;1.000000;,
  52;1.000000;1.000000;1.000000;1.000000;,
  53;1.000000;1.000000;1.000000;1.000000;,
  54;1.000000;1.000000;1.000000;1.000000;,
  55;1.000000;1.000000;1.000000;1.000000;,
  56;1.000000;1.000000;1.000000;1.000000;,
  57;1.000000;1.000000;1.000000;1.000000;,
  58;1.000000;1.000000;1.000000;1.000000;,
  59;1.000000;1.000000;1.000000;1.000000;,
  60;1.000000;1.000000;1.000000;1.000000;,
  61;1.000000;1.000000;1.000000;1.000000;,
  62;1.000000;1.000000;1.000000;1.000000;,
  63;1.000000;1.000000;1.000000;1.000000;,
  64;1.000000;1.000000;1.000000;1.000000;,
  65;1.000000;1.000000;1.000000;1.000000;,
  66;1.000000;1.000000;1.000000;1.000000;,
  67;1.000000;1.000000;1.000000;1.000000;,
  68;1.000000;1.000000;1.000000;1.000000;,
  69;1.000000;1.000000;1.000000;1.000000;,
  70;1.000000;1.000000;1.000000;1.000000;,
  71;1.000000;1.000000;1.000000;1.000000;,
  72;1.000000;1.000000;1.000000;1.000000;,
  73;1.000000;1.000000;1.000000;1.000000;,
  74;1.000000;1.000000;1.000000;1.000000;,
  75;1.000000;1.000000;1.000000;1.000000;,
  76;1.000000;1.000000;1.000000;1.000000;,
  77;1.000000;1.000000;1.000000;1.000000;;
 }
}