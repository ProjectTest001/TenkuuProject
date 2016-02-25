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
 -0.00424;0.00280;-0.02371;,
 -0.00256;-0.24836;-0.03151;,
 -0.01177;-0.24854;-0.02785;,
 -0.01345;0.00263;-0.02005;,
 -0.01869;-0.24881;-0.02076;,
 -0.02037;0.00236;-0.01296;,
 -0.02213;-0.24912;-0.01147;,
 -0.02381;0.00205;-0.00367;,
 -0.02149;-0.24942;-0.00158;,
 -0.02317;0.00175;0.00622;,
 -0.01688;-0.24966;0.00719;,
 -0.01856;0.00151;0.01499;,
 -0.00910;-0.24980;0.01333;,
 -0.01078;0.00137;0.02113;,
 0.00050;-0.24981;0.01578;,
 -0.00118;0.00136;0.02358;,
 0.01027;-0.24969;0.01411;,
 0.00859;0.00147;0.02191;,
 0.01851;-0.24947;0.00861;,
 0.01683;0.00170;0.01642;,
 0.02381;-0.24917;0.00024;,
 0.02213;0.00199;0.00805;,
 0.02524;-0.24886;-0.00956;,
 0.02356;0.00231;-0.00176;,
 0.02256;-0.24858;-0.01910;,
 0.02088;0.00259;-0.01129;,
 0.01623;-0.24839;-0.02672;,
 0.01455;0.00278;-0.01892;,
 0.00734;-0.24831;-0.03111;,
 0.00566;0.00286;-0.02331;,
 -0.00256;-0.24836;-0.03151;,
 -0.00424;0.00280;-0.02371;,
 -0.00022;0.00210;-0.00022;,
 -0.00022;0.00210;-0.00022;,
 -0.00022;0.00210;-0.00022;,
 -0.00022;0.00210;-0.00022;,
 -0.00022;0.00210;-0.00022;,
 -0.00022;0.00210;-0.00022;,
 -0.00022;0.00210;-0.00022;,
 -0.00022;0.00210;-0.00022;,
 -0.00022;0.00210;-0.00022;,
 -0.00022;0.00210;-0.00022;,
 -0.00022;0.00210;-0.00022;,
 -0.00022;0.00210;-0.00022;,
 -0.00022;0.00210;-0.00022;,
 -0.00022;0.00210;-0.00022;,
 -0.00022;0.00210;-0.00022;,
 0.00152;-0.24927;-0.00737;,
 -0.01170;-0.24874;-0.02719;,
 -0.00249;-0.24856;-0.03086;,
 0.00152;-0.24927;-0.00737;,
 -0.01862;-0.24900;-0.02011;,
 0.00152;-0.24927;-0.00737;,
 -0.02206;-0.24932;-0.01082;,
 0.00152;-0.24927;-0.00737;,
 -0.02142;-0.24962;-0.00093;,
 0.00152;-0.24927;-0.00737;,
 -0.01681;-0.24986;0.00784;,
 0.00152;-0.24927;-0.00737;,
 -0.00903;-0.25000;0.01398;,
 0.00152;-0.24927;-0.00737;,
 0.00057;-0.25001;0.01643;,
 0.00152;-0.24927;-0.00737;,
 0.01034;-0.24989;0.01476;,
 0.00152;-0.24927;-0.00737;,
 0.01858;-0.24967;0.00927;,
 0.00152;-0.24927;-0.00737;,
 0.02388;-0.24937;0.00090;,
 0.00152;-0.24927;-0.00737;,
 0.02531;-0.24906;-0.00891;,
 0.00152;-0.24927;-0.00737;,
 0.02262;-0.24878;-0.01844;,
 0.00152;-0.24927;-0.00737;,
 0.01629;-0.24858;-0.02607;,
 0.00152;-0.24927;-0.00737;,
 0.00741;-0.24851;-0.03046;,
 0.00152;-0.24927;-0.00737;,
 -0.00249;-0.24856;-0.03086;;
 
 45;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;17,16,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;23,22,24,25;,
 4;25,24,26,27;,
 4;27,26,28,29;,
 4;29,28,30,31;,
 3;32,0,3;,
 3;33,3,5;,
 3;34,5,7;,
 3;35,7,9;,
 3;36,9,11;,
 3;37,11,13;,
 3;38,13,15;,
 3;39,15,17;,
 3;40,17,19;,
 3;41,19,21;,
 3;42,21,23;,
 3;43,23,25;,
 3;44,25,27;,
 3;45,27,29;,
 3;46,29,31;,
 3;47,48,49;,
 3;50,51,48;,
 3;52,53,51;,
 3;54,55,53;,
 3;56,57,55;,
 3;58,59,57;,
 3;60,61,59;,
 3;62,63,61;,
 3;64,65,63;,
 3;66,67,65;,
 3;68,69,67;,
 3;70,71,69;,
 3;72,73,71;,
 3;74,75,73;,
 3;76,77,75;;
 
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
  -0.006681;0.999496;0.031045;,
  -0.168529;0.029487;-0.985255;,
  -0.554896;0.022129;-0.831626;,
  -0.845298;0.010945;-0.534183;,
  -0.989515;-0.002129;-0.144414;,
  -0.962659;-0.014837;0.270312;,
  -0.769369;-0.024981;0.638316;,
  -0.443011;-0.030805;0.895987;,
  -0.040037;-0.031300;0.998708;,
  0.369832;-0.026384;0.928724;,
  0.715710;-0.016908;0.698193;,
  0.937872;-0.004507;0.346953;,
  0.997892;0.008672;-0.064318;,
  0.885355;0.020352;-0.464469;,
  0.619707;0.028516;-0.784315;,
  0.246898;0.031746;-0.968521;,
  0.006699;-0.999494;-0.031097;,
  0.006705;-0.999493;-0.031129;,
  0.006734;-0.999493;-0.031118;,
  0.006694;-0.999496;-0.031020;,
  0.006671;-0.999496;-0.031033;,
  0.006678;-0.999495;-0.031064;,
  0.006680;-0.999496;-0.031047;,
  0.006678;-0.999495;-0.031057;,
  0.006685;-0.999495;-0.031051;,
  0.006686;-0.999495;-0.031060;,
  0.006704;-0.999494;-0.031086;,
  0.006710;-0.999495;-0.031058;,
  0.006676;-0.999494;-0.031090;,
  0.006662;-0.999493;-0.031142;,
  0.006719;-0.999493;-0.031116;,
  0.006692;-0.999494;-0.031078;,
  -0.006671;0.999498;0.030967;,
  -0.006602;0.999497;0.031009;,
  -0.006732;0.999493;0.031115;,
  -0.006740;0.999495;0.031063;,
  -0.006722;0.999497;0.031000;,
  -0.006679;0.999495;0.031066;,
  -0.006656;0.999494;0.031104;,
  -0.006726;0.999494;0.031095;,
  -0.006729;0.999495;0.031071;,
  -0.006652;0.999497;0.031025;,
  -0.006647;0.999496;0.031054;,
  -0.006674;0.999497;0.031006;,
  -0.006628;0.999497;0.031005;,
  -0.006611;0.999495;0.031077;,
  -0.006748;0.999496;0.031023;;
  45;
  4;1,1,2,2;,
  4;2,2,3,3;,
  4;3,3,4,4;,
  4;4,4,5,5;,
  4;5,5,6,6;,
  4;6,6,7,7;,
  4;7,7,8,8;,
  4;8,8,9,9;,
  4;9,9,10,10;,
  4;10,10,11,11;,
  4;11,11,12,12;,
  4;12,12,13,13;,
  4;13,13,14,14;,
  4;14,14,15,15;,
  4;15,15,1,1;,
  3;0,32,33;,
  3;0,33,34;,
  3;0,34,35;,
  3;0,35,36;,
  3;0,36,37;,
  3;0,37,38;,
  3;0,38,39;,
  3;0,39,40;,
  3;0,40,41;,
  3;0,41,42;,
  3;0,42,43;,
  3;0,43,44;,
  3;0,44,45;,
  3;0,45,46;,
  3;0,46,32;,
  3;31,17,16;,
  3;31,18,17;,
  3;31,19,18;,
  3;31,20,19;,
  3;31,21,20;,
  3;31,22,21;,
  3;31,23,22;,
  3;31,24,23;,
  3;31,25,24;,
  3;31,26,25;,
  3;31,27,26;,
  3;31,28,27;,
  3;31,29,28;,
  3;31,30,29;,
  3;31,16,30;;
 }
 MeshTextureCoords {
  78;
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.066670;0.333330;,
  0.066670;0.000000;,
  0.133330;0.333330;,
  0.133330;0.000000;,
  0.200000;0.333330;,
  0.200000;0.000000;,
  0.266670;0.333330;,
  0.266670;0.000000;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.400000;0.333330;,
  0.400000;0.000000;,
  0.466670;0.333330;,
  0.466670;0.000000;,
  0.533330;0.333330;,
  0.533330;0.000000;,
  0.600000;0.333330;,
  0.600000;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  0.733330;0.333330;,
  0.733330;0.000000;,
  0.800000;0.333330;,
  0.800000;0.000000;,
  0.866670;0.333330;,
  0.866670;0.000000;,
  0.933330;0.333330;,
  0.933330;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
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
  0.066670;1.000000;,
  0.000000;1.000000;,
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