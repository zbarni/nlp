#include<vector>
#include<string>

// simple character based bigram language model
//   * the vocabulary is stored in vector<string> vocab;
//   * bigrams are stored in vector<vector<double>> scores;
//
// to use, simply add the following lines to your code:
//   #include "simple_lm.hh"
//
//   ...
//
//   init_vocab();
//   init_lm();
//
//
//
// example usage to obtain p("i" | "h"):
//   * index of token "h" is 11, since vocab[11] == "h"
//   * index of token "i" is 12, since vocab[12] == "i"
//   * scores[11][12] = log( prob("i" | "h") )
//   * log == logarithm to base e
//
// note that for the beginning of a sequence you might need
//   * p("h" | "<s>") or similar
//
// and for the end of a sentence
//   * p("</s>" | "i") or similar

std::vector<std::string> vocab(30);
std::vector<std::vector<double> > scores(30, std::vector<double> (30, 0.0));

void init_vocab() {
  vocab[0] = "<unk>";
  vocab[1] = "</s>";
  vocab[2] = "<s>";
  vocab[3] = "_";
  vocab[4] = "a";
  vocab[5] = "b";
  vocab[6] = "c";
  vocab[7] = "d";
  vocab[8] = "e";
  vocab[9] = "f";
  vocab[10] = "g";
  vocab[11] = "h";
  vocab[12] = "i";
  vocab[13] = "j";
  vocab[14] = "k";
  vocab[15] = "l";
  vocab[16] = "m";
  vocab[17] = "n";
  vocab[18] = "o";
  vocab[19] = "p";
  vocab[20] = "q";
  vocab[21] = "r";
  vocab[22] = "s";
  vocab[23] = "t";
  vocab[24] = "u";
  vocab[25] = "v";
  vocab[26] = "w";
  vocab[27] = "x";
  vocab[28] = "y";
  vocab[29] = "z";
};

void init_lm() {
  scores[0][0]=-100;
  scores[0][1]=-2.14736;
  scores[0][2]=-99;
  scores[0][3]=-0.797561;
  scores[0][4]=-1.12217;
  scores[0][5]=-1.89106;
  scores[0][6]=-1.58348;
  scores[0][7]=-1.45504;
  scores[0][8]=-1.00043;
  scores[0][9]=-1.73403;
  scores[0][10]=-1.77527;
  scores[0][11]=-1.42915;
  scores[0][12]=-1.1894;
  scores[0][13]=-2.76686;
  scores[0][14]=-2.16932;
  scores[0][15]=-1.48039;
  scores[0][16]=-1.6959;
  scores[0][17]=-1.21105;
  scores[0][18]=-1.22597;
  scores[0][19]=-1.73956;
  scores[0][20]=-3.03945;
  scores[0][21]=-1.26377;
  scores[0][22]=-1.2471;
  scores[0][23]=-1.13007;
  scores[0][24]=-1.63431;
  scores[0][25]=-2.09366;
  scores[0][26]=-1.86255;
  scores[0][27]=-2.87669;
  scores[0][28]=-1.89832;
  scores[0][29]=-2.98239;
  scores[1][0]=-100;
  scores[1][1]=-2.14736;
  scores[1][2]=-99;
  scores[1][3]=-0.797561;
  scores[1][4]=-1.12217;
  scores[1][5]=-1.89106;
  scores[1][6]=-1.58348;
  scores[1][7]=-1.45504;
  scores[1][8]=-1.00043;
  scores[1][9]=-1.73403;
  scores[1][10]=-1.77527;
  scores[1][11]=-1.42915;
  scores[1][12]=-1.1894;
  scores[1][13]=-2.76686;
  scores[1][14]=-2.16932;
  scores[1][15]=-1.48039;
  scores[1][16]=-1.6959;
  scores[1][17]=-1.21105;
  scores[1][18]=-1.22597;
  scores[1][19]=-1.73956;
  scores[1][20]=-3.03945;
  scores[1][21]=-1.26377;
  scores[1][22]=-1.2471;
  scores[1][23]=-1.13007;
  scores[1][24]=-1.63431;
  scores[1][25]=-2.09366;
  scores[1][26]=-1.86255;
  scores[1][27]=-2.87669;
  scores[1][28]=-1.89832;
  scores[1][29]=-2.98239;
  scores[2][0]=-104.103;
  scores[2][1]=-6.25058;
  scores[2][2]=-103.103;
  scores[2][3]=-4.90078;
  scores[2][4]=-0.971713;
  scores[2][5]=-1.13196;
  scores[2][6]=-1.48082;
  scores[2][7]=-1.64791;
  scores[2][8]=-1.63057;
  scores[2][9]=-1.57168;
  scores[2][10]=-1.78533;
  scores[2][11]=-1.18996;
  scores[2][12]=-1.18614;
  scores[2][13]=-1.95882;
  scores[2][14]=-1.97079;
  scores[2][15]=-1.74833;
  scores[2][16]=-1.44906;
  scores[2][17]=-1.72151;
  scores[2][18]=-1.58542;
  scores[2][19]=-1.40251;
  scores[2][20]=-2.87734;
  scores[2][21]=-1.60683;
  scores[2][22]=-1.2253;
  scores[2][23]=-0.586012;
  scores[2][24]=-1.56898;
  scores[2][25]=-2.21885;
  scores[2][26]=-1.62603;
  scores[2][27]=-3.50445;
  scores[2][28]=-2.49303;
  scores[2][29]=-2.56118;
  scores[3][0]=-104.743;
  scores[3][1]=-6.88994;
  scores[3][2]=-103.743;
  scores[3][3]=-5.54015;
  scores[3][4]=-0.938023;
  scores[3][5]=-1.30753;
  scores[3][6]=-1.26645;
  scores[3][7]=-1.51005;
  scores[3][8]=-1.62053;
  scores[3][9]=-1.34027;
  scores[3][10]=-1.75788;
  scores[3][11]=-1.35534;
  scores[3][12]=-1.1993;
  scores[3][13]=-2.19805;
  scores[3][14]=-2.15389;
  scores[3][15]=-1.66421;
  scores[3][16]=-1.4252;
  scores[3][17]=-1.68436;
  scores[3][18]=-1.18388;
  scores[3][19]=-1.35465;
  scores[3][20]=-2.77748;
  scores[3][21]=-1.46692;
  scores[3][22]=-1.11022;
  scores[3][23]=-0.80965;
  scores[3][24]=-1.79372;
  scores[3][25]=-2.15317;
  scores[3][26]=-1.24758;
  scores[3][27]=-3.87047;
  scores[3][28]=-2.4247;
  scores[3][29]=-2.97874;
  scores[4][0]=-100;
  scores[4][1]=-2.48207;
  scores[4][2]=-99;
  scores[4][3]=-1.08855;
  scores[4][4]=-3.19633;
  scores[4][5]=-1.84132;
  scores[4][6]=-1.44484;
  scores[4][7]=-1.36402;
  scores[4][8]=-2.32311;
  scores[4][9]=-1.76591;
  scores[4][10]=-1.69063;
  scores[4][11]=-2.31889;
  scores[4][12]=-1.23577;
  scores[4][13]=-2.62698;
  scores[4][14]=-1.86936;
  scores[4][15]=-1.00134;
  scores[4][16]=-1.54205;
  scores[4][17]=-0.761779;
  scores[4][18]=-3.01581;
  scores[4][19]=-1.78804;
  scores[4][20]=-2.39996;
  scores[4][21]=-1.01055;
  scores[4][22]=-1.07925;
  scores[4][23]=-0.937536;
  scores[4][24]=-1.87832;
  scores[4][25]=-1.75217;
  scores[4][26]=-2.20915;
  scores[4][27]=-2.99698;
  scores[4][28]=-1.39939;
  scores[4][29]=-2.54988;
  scores[5][0]=-100;
  scores[5][1]=-2.81627;
  scores[5][2]=-99;
  scores[5][3]=-1.68792;
  scores[5][4]=-0.836331;
  scores[5][5]=-2.09377;
  scores[5][6]=-2.86807;
  scores[5][7]=-2.40319;
  scores[5][8]=-0.568214;
  scores[5][9]=-4.14333;
  scores[5][10]=-4.32335;
  scores[5][11]=-2.82101;
  scores[5][12]=-1.25306;
  scores[5][13]=-2.61462;
  scores[5][14]=-3.42528;
  scores[5][15]=-1.06688;
  scores[5][16]=-2.75861;
  scores[5][17]=-3.23906;
  scores[5][18]=-1.00752;
  scores[5][19]=-3.02824;
  scores[5][20]=-5.59697;
  scores[5][21]=-1.19276;
  scores[5][22]=-1.82184;
  scores[5][23]=-2.32133;
  scores[5][24]=-0.943631;
  scores[5][25]=-3.53532;
  scores[5][26]=-2.67315;
  scores[5][27]=-5.59641;
  scores[5][28]=-0.996951;
  scores[5][29]=-4.4384;
  scores[6][0]=-100;
  scores[6][1]=-2.83956;
  scores[6][2]=-99;
  scores[6][3]=-1.45245;
  scores[6][4]=-0.953585;
  scores[6][5]=-3.28076;
  scores[6][6]=-1.70576;
  scores[6][7]=-3.41224;
  scores[6][8]=-0.796566;
  scores[6][9]=-3.99461;
  scores[6][10]=-3.63485;
  scores[6][11]=-0.903805;
  scores[6][12]=-1.13448;
  scores[6][13]=-4.26117;
  scores[6][14]=-1.31053;
  scores[6][15]=-1.38792;
  scores[6][16]=-3.87614;
  scores[6][17]=-3.5319;
  scores[6][18]=-0.719773;
  scores[6][19]=-3.75672;
  scores[6][20]=-2.9187;
  scores[6][21]=-1.36203;
  scores[6][22]=-2.43022;
  scores[6][23]=-1.0859;
  scores[6][24]=-1.31666;
  scores[6][25]=-4.48853;
  scores[6][26]=-4.55599;
  scores[6][27]=-5.65489;
  scores[6][28]=-1.90767;
  scores[6][29]=-3.04271;
  scores[7][0]=-100;
  scores[7][1]=-1.66559;
  scores[7][2]=-99;
  scores[7][3]=-0.288173;
  scores[7][4]=-1.10486;
  scores[7][5]=-3.35093;
  scores[7][6]=-3.09604;
  scores[7][7]=-2.0779;
  scores[7][8]=-0.786779;
  scores[7][9]=-2.95333;
  scores[7][10]=-2.30192;
  scores[7][11]=-2.88308;
  scores[7][12]=-1.09336;
  scores[7][13]=-3.08907;
  scores[7][14]=-3.96185;
  scores[7][15]=-2.1101;
  scores[7][16]=-2.39992;
  scores[7][17]=-2.02856;
  scores[7][18]=-1.501;
  scores[7][19]=-3.56908;
  scores[7][20]=-3.32147;
  scores[7][21]=-1.78613;
  scores[7][22]=-1.71894;
  scores[7][23]=-3.5843;
  scores[7][24]=-1.64544;
  scores[7][25]=-2.57731;
  scores[7][26]=-2.95337;
  scores[7][27]=-5.46945;
  scores[7][28]=-2.15994;
  scores[7][29]=-3.38748;
  scores[8][0]=-100;
  scores[8][1]=-2.08165;
  scores[8][2]=-99;
  scores[8][3]=-0.552922;
  scores[8][4]=-1.26655;
  scores[8][5]=-2.41195;
  scores[8][6]=-1.49159;
  scores[8][7]=-1.02432;
  scores[8][8]=-1.56727;
  scores[8][9]=-1.91306;
  scores[8][10]=-2.03506;
  scores[8][11]=-2.68582;
  scores[8][12]=-1.82559;
  scores[8][13]=-3.15958;
  scores[8][14]=-2.29545;
  scores[8][15]=-1.47064;
  scores[8][16]=-1.68471;
  scores[8][17]=-1.05168;
  scores[8][18]=-2.52848;
  scores[8][19]=-1.86925;
  scores[8][20]=-2.84034;
  scores[8][21]=-0.878588;
  scores[8][22]=-1.0499;
  scores[8][23]=-1.56859;
  scores[8][24]=-2.29806;
  scores[8][25]=-1.91984;
  scores[8][26]=-2.05115;
  scores[8][27]=-1.95957;
  scores[8][28]=-2.10043;
  scores[8][29]=-2.91716;
  scores[9][0]=-100;
  scores[9][1]=-2.65389;
  scores[9][2]=-99;
  scores[9][3]=-0.544501;
  scores[9][4]=-1.30082;
  scores[9][5]=-3.43917;
  scores[9][6]=-3.53812;
  scores[9][7]=-3.74146;
  scores[9][8]=-1.17784;
  scores[9][9]=-1.16949;
  scores[9][10]=-2.27873;
  scores[9][11]=-4.58223;
  scores[9][12]=-0.919437;
  scores[9][13]=-4.12171;
  scores[9][14]=-3.92543;
  scores[9][15]=-1.63284;
  scores[9][16]=-3.58773;
  scores[9][17]=-3.70184;
  scores[9][18]=-0.727886;
  scores[9][19]=-2.36417;
  scores[9][20]=-5.34726;
  scores[9][21]=-1.0146;
  scores[9][22]=-2.6123;
  scores[9][23]=-1.29549;
  scores[9][24]=-1.48012;
  scores[9][25]=-5.3435;
  scores[9][26]=-4.02518;
  scores[9][27]=-5.29388;
  scores[9][28]=-2.47609;
  scores[9][29]=-4.69232;
  scores[10][0]=-100;
  scores[10][1]=-1.9857;
  scores[10][2]=-99;
  scores[10][3]=-0.473131;
  scores[10][4]=-1.05649;
  scores[10][5]=-2.67881;
  scores[10][6]=-3.5763;
  scores[10][7]=-2.96649;
  scores[10][8]=-0.81658;
  scores[10][9]=-3.74992;
  scores[10][10]=-1.88901;
  scores[10][11]=-1.06742;
  scores[10][12]=-1.29246;
  scores[10][13]=-3.95554;
  scores[10][14]=-3.1918;
  scores[10][15]=-1.64264;
  scores[10][16]=-2.95427;
  scores[10][17]=-1.47248;
  scores[10][18]=-1.19474;
  scores[10][19]=-3.60961;
  scores[10][20]=-4.3737;
  scores[10][21]=-1.17167;
  scores[10][22]=-1.8294;
  scores[10][23]=-2.09;
  scores[10][24]=-1.44153;
  scores[10][25]=-4.54039;
  scores[10][26]=-3.57014;
  scores[10][27]=-4.36929;
  scores[10][28]=-1.98527;
  scores[10][29]=-3.92235;
  scores[11][0]=-100;
  scores[11][1]=-2.38198;
  scores[11][2]=-99;
  scores[11][3]=-0.949044;
  scores[11][4]=-0.783061;
  scores[11][5]=-2.80415;
  scores[11][6]=-3.36406;
  scores[11][7]=-2.52259;
  scores[11][8]=-0.325265;
  scores[11][9]=-3.77667;
  scores[11][10]=-4.27125;
  scores[11][11]=-3.8792;
  scores[11][12]=-0.997358;
  scores[11][13]=-4.61981;
  scores[11][14]=-3.53618;
  scores[11][15]=-2.71024;
  scores[11][16]=-2.42603;
  scores[11][17]=-2.42675;
  scores[11][18]=-1.14555;
  scores[11][19]=-3.61114;
  scores[11][20]=-3.63214;
  scores[11][21]=-1.95081;
  scores[11][22]=-2.53049;
  scores[11][23]=-1.70843;
  scores[11][24]=-1.68169;
  scores[11][25]=-3.78846;
  scores[11][26]=-2.92017;
  scores[11][27]=-6.53187;
  scores[11][28]=-2.67566;
  scores[11][29]=-4.78382;
  scores[12][0]=-100;
  scores[12][1]=-3.05098;
  scores[12][2]=-99;
  scores[12][3]=-1.78245;
  scores[12][4]=-1.28707;
  scores[12][5]=-2.15941;
  scores[12][6]=-1.16849;
  scores[12][7]=-1.19566;
  scores[12][8]=-1.4311;
  scores[12][9]=-1.98876;
  scores[12][10]=-1.54692;
  scores[12][11]=-3.42441;
  scores[12][12]=-3.09529;
  scores[12][13]=-2.89538;
  scores[12][14]=-2.30093;
  scores[12][15]=-1.27552;
  scores[12][16]=-1.55714;
  scores[12][17]=-0.577022;
  scores[12][18]=-1.15056;
  scores[12][19]=-2.04584;
  scores[12][20]=-3.30271;
  scores[12][21]=-1.39583;
  scores[12][22]=-0.981063;
  scores[12][23]=-0.954982;
  scores[12][24]=-2.89856;
  scores[12][25]=-1.66925;
  scores[12][26]=-3.22126;
  scores[12][27]=-3.05751;
  scores[12][28]=-3.25526;
  scores[12][29]=-2.48913;
  scores[13][0]=-101.369;
  scores[13][1]=-3.26673;
  scores[13][2]=-100.369;
  scores[13][3]=-2.07146;
  scores[13][4]=-0.61653;
  scores[13][5]=-3.35651;
  scores[13][6]=-3.27526;
  scores[13][7]=-2.88637;
  scores[13][8]=-0.837258;
  scores[13][9]=-3.70818;
  scores[13][10]=-4.21426;
  scores[13][11]=-3.3093;
  scores[13][12]=-1.10675;
  scores[13][13]=-2.76391;
  scores[13][14]=-2.72923;
  scores[13][15]=-3.45394;
  scores[13][16]=-2.97769;
  scores[13][17]=-3.19236;
  scores[13][18]=-0.546285;
  scores[13][19]=-2.27837;
  scores[13][20]=-5.37563;
  scores[13][21]=-3.12643;
  scores[13][22]=-2.7452;
  scores[13][23]=-3.59387;
  scores[13][24]=-0.650266;
  scores[13][25]=-3.54312;
  scores[13][26]=-3.56272;
  scores[13][27]=-4.24538;
  scores[13][28]=-3.90581;
  scores[13][29]=-4.37563;
  scores[14][0]=-100;
  scores[14][1]=-1.69346;
  scores[14][2]=-99;
  scores[14][3]=-0.653865;
  scores[14][4]=-1.24978;
  scores[14][5]=-2.77665;
  scores[14][6]=-3.4355;
  scores[14][7]=-2.45425;
  scores[14][8]=-0.511042;
  scores[14][9]=-2.85216;
  scores[14][10]=-3.13227;
  scores[14][11]=-1.79341;
  scores[14][12]=-0.86407;
  scores[14][13]=-3.61517;
  scores[14][14]=-2.7232;
  scores[14][15]=-1.86457;
  scores[14][16]=-2.77607;
  scores[14][17]=-1.74803;
  scores[14][18]=-1.27142;
  scores[14][19]=-2.52526;
  scores[14][20]=-6.26322;
  scores[14][21]=-2.03034;
  scores[14][22]=-0.997146;
  scores[14][23]=-2.53122;
  scores[14][24]=-1.83514;
  scores[14][25]=-3.86387;
  scores[14][26]=-2.79556;
  scores[14][27]=-4.65055;
  scores[14][28]=-1.93756;
  scores[14][29]=-4.15024;
  scores[15][0]=-100;
  scores[15][1]=-2.17454;
  scores[15][2]=-99;
  scores[15][3]=-0.788602;
  scores[15][4]=-0.910666;
  scores[15][5]=-2.79679;
  scores[15][6]=-2.74957;
  scores[15][7]=-1.21132;
  scores[15][8]=-0.801349;
  scores[15][9]=-2.24634;
  scores[15][10]=-2.68188;
  scores[15][11]=-3.12773;
  scores[15][12]=-0.84717;
  scores[15][13]=-3.82479;
  scores[15][14]=-2.04251;
  scores[15][15]=-0.978942;
  scores[15][16]=-2.44359;
  scores[15][17]=-3.29699;
  scores[15][18]=-1.17415;
  scores[15][19]=-2.34028;
  scores[15][20]=-4.69588;
  scores[15][21]=-2.56474;
  scores[15][22]=-1.37829;
  scores[15][23]=-1.74466;
  scores[15][24]=-1.73241;
  scores[15][25]=-2.29494;
  scores[15][26]=-3.18479;
  scores[15][27]=-6.058;
  scores[15][28]=-1.24052;
  scores[15][29]=-3.97365;
  scores[16][0]=-100;
  scores[16][1]=-2.12559;
  scores[16][2]=-99;
  scores[16][3]=-0.97592;
  scores[16][4]=-0.734862;
  scores[16][5]=-1.41933;
  scores[16][6]=-2.61647;
  scores[16][7]=-3.45734;
  scores[16][8]=-0.609539;
  scores[16][9]=-2.95293;
  scores[16][10]=-4.00686;
  scores[16][11]=-3.96725;
  scores[16][12]=-0.825087;
  scores[16][13]=-4.26039;
  scores[16][14]=-3.80649;
  scores[16][15]=-2.86263;
  scores[16][16]=-1.42994;
  scores[16][17]=-2.58678;
  scores[16][18]=-0.98289;
  scores[16][19]=-1.22785;
  scores[16][20]=-4.36016;
  scores[16][21]=-3.21084;
  scores[16][22]=-1.65357;
  scores[16][23]=-3.6517;
  scores[16][24]=-1.57881;
  scores[16][25]=-4.01182;
  scores[16][26]=-3.44087;
  scores[16][27]=-4.92781;
  scores[16][28]=-1.97387;
  scores[16][29]=-3.98116;
  scores[17][0]=-100;
  scores[17][1]=-1.99068;
  scores[17][2]=-99;
  scores[17][3]=-0.562933;
  scores[17][4]=-1.34912;
  scores[17][5]=-3.15192;
  scores[17][6]=-1.37094;
  scores[17][7]=-0.920429;
  scores[17][8]=-1.12303;
  scores[17][9]=-2.11259;
  scores[17][10]=-0.947433;
  scores[17][11]=-2.91413;
  scores[17][12]=-1.28063;
  scores[17][13]=-2.65646;
  scores[17][14]=-2.09865;
  scores[17][15]=-2.38446;
  scores[17][16]=-2.05695;
  scores[17][17]=-2.01749;
  scores[17][18]=-1.42812;
  scores[17][19]=-3.15765;
  scores[17][20]=-3.36669;
  scores[17][21]=-2.95249;
  scores[17][22]=-1.27233;
  scores[17][23]=-0.975955;
  scores[17][24]=-2.08515;
  scores[17][25]=-2.11204;
  scores[17][26]=-2.90766;
  scores[17][27]=-3.88609;
  scores[17][28]=-2.03266;
  scores[17][29]=-3.21399;
  scores[18][0]=-100;
  scores[18][1]=-2.84422;
  scores[18][2]=-99;
  scores[18][3]=-0.855832;
  scores[18][4]=-2.0789;
  scores[18][5]=-2.04366;
  scores[18][6]=-1.82085;
  scores[18][7]=-2.00451;
  scores[18][8]=-2.68639;
  scores[18][9]=-1.03633;
  scores[18][10]=-2.23501;
  scores[18][11]=-2.69111;
  scores[18][12]=-2.01062;
  scores[18][13]=-3.09876;
  scores[18][14]=-2.09093;
  scores[18][15]=-1.37949;
  scores[18][16]=-1.25433;
  scores[18][17]=-0.725052;
  scores[18][18]=-1.72449;
  scores[18][19]=-1.51015;
  scores[18][20]=-4.05705;
  scores[18][21]=-0.868676;
  scores[18][22]=-1.49092;
  scores[18][23]=-1.43076;
  scores[18][24]=-1.05607;
  scores[18][25]=-1.51402;
  scores[18][26]=-1.51109;
  scores[18][27]=-3.15359;
  scores[18][28]=-2.35777;
  scores[18][29]=-2.80818;
  scores[19][0]=-100;
  scores[19][1]=-2.31802;
  scores[19][2]=-99;
  scores[19][3]=-1.14359;
  scores[19][4]=-0.869784;
  scores[19][5]=-3.22402;
  scores[19][6]=-3.05678;
  scores[19][7]=-3.20042;
  scores[19][8]=-0.789199;
  scores[19][9]=-3.64607;
  scores[19][10]=-3.32292;
  scores[19][11]=-1.80802;
  scores[19][12]=-1.29431;
  scores[19][13]=-4.0664;
  scores[19][14]=-3.38458;
  scores[19][15]=-1.09939;
  scores[19][16]=-2.37907;
  scores[19][17]=-3.47818;
  scores[19][18]=-0.791599;
  scores[19][19]=-1.27631;
  scores[19][20]=-5.70283;
  scores[19][21]=-0.78076;
  scores[19][22]=-1.65778;
  scores[19][23]=-1.54855;
  scores[19][24]=-1.4153;
  scores[19][25]=-4.70296;
  scores[19][26]=-3.54909;
  scores[19][27]=-5.85654;
  scores[19][28]=-2.52346;
  scores[19][29]=-4.71258;
  scores[20][0]=-101.096;
  scores[20][1]=-1.35728;
  scores[20][2]=-100.096;
  scores[20][3]=-0.776515;
  scores[20][4]=-1.57228;
  scores[20][5]=-3.0519;
  scores[20][6]=-4.19997;
  scores[20][7]=-3.7913;
  scores[20][8]=-2.93279;
  scores[20][9]=-3.86002;
  scores[20][10]=-4.62594;
  scores[20][11]=-4.40409;
  scores[20][12]=-0.911619;
  scores[20][13]=-4.80203;
  scores[20][14]=-5.40409;
  scores[20][15]=-3.44984;
  scores[20][16]=-3.42636;
  scores[20][17]=-3.91272;
  scores[20][18]=-2.19861;
  scores[20][19]=-3.60474;
  scores[20][20]=-3.35101;
  scores[20][21]=-3.71389;
  scores[20][22]=-3.28681;
  scores[20][23]=-2.65281;
  scores[20][24]=-0.20415;
  scores[20][25]=-3.2935;
  scores[20][26]=-3.34339;
  scores[20][27]=-3.97272;
  scores[20][28]=-4.22799;
  scores[20][29]=-4.40409;
  scores[21][0]=-100;
  scores[21][1]=-2.12469;
  scores[21][2]=-99;
  scores[21][3]=-0.766145;
  scores[21][4]=-1.03841;
  scores[21][5]=-2.44592;
  scores[21][6]=-1.8492;
  scores[21][7]=-1.65389;
  scores[21][8]=-0.674725;
  scores[21][9]=-2.68282;
  scores[21][10]=-1.78948;
  scores[21][11]=-3.02744;
  scores[21][12]=-0.993775;
  scores[21][13]=-3.9293;
  scores[21][14]=-1.8506;
  scores[21][15]=-1.84796;
  scores[21][16]=-1.64145;
  scores[21][17]=-1.47562;
  scores[21][18]=-1.04247;
  scores[21][19]=-2.38078;
  scores[21][20]=-4.20429;
  scores[21][21]=-1.75512;
  scores[21][22]=-1.24812;
  scores[21][23]=-1.31437;
  scores[21][24]=-1.69715;
  scores[21][25]=-2.19747;
  scores[21][26]=-2.68217;
  scores[21][27]=-4.75971;
  scores[21][28]=-1.57885;
  scores[21][29]=-3.31891;
  scores[22][0]=-100;
  scores[22][1]=-1.56235;
  scores[22][2]=-99;
  scores[22][3]=-0.448725;
  scores[22][4]=-1.23613;
  scores[22][5]=-3.10708;
  scores[22][6]=-1.87725;
  scores[22][7]=-1.83694;
  scores[22][8]=-1.01383;
  scores[22][9]=-2.88524;
  scores[22][10]=-3.60897;
  scores[22][11]=-1.39848;
  scores[22][12]=-1.16361;
  scores[22][13]=-4.59104;
  scores[22][14]=-2.35744;
  scores[22][15]=-2.01873;
  scores[22][16]=-2.14046;
  scores[22][17]=-2.75987;
  scores[22][18]=-1.4297;
  scores[22][19]=-1.59023;
  scores[22][20]=-2.95589;
  scores[22][21]=-2.22107;
  scores[22][22]=-1.35687;
  scores[22][23]=-0.846024;
  scores[22][24]=-1.44062;
  scores[22][25]=-3.7236;
  scores[22][26]=-2.48762;
  scores[22][27]=-5.62776;
  scores[22][28]=-2.41638;
  scores[22][29]=-4.00493;
  scores[23][0]=-100;
  scores[23][1]=-2.12042;
  scores[23][2]=-99;
  scores[23][3]=-0.731942;
  scores[23][4]=-1.2347;
  scores[23][5]=-3.00569;
  scores[23][6]=-2.48435;
  scores[23][7]=-3.85676;
  scores[23][8]=-0.938649;
  scores[23][9]=-3.45372;
  scores[23][10]=-3.55071;
  scores[23][11]=-0.574827;
  scores[23][12]=-0.993038;
  scores[23][13]=-4.80957;
  scores[23][14]=-4.00976;
  scores[23][15]=-2.15971;
  scores[23][16]=-2.62073;
  scores[23][17]=-2.8477;
  scores[23][18]=-0.960902;
  scores[23][19]=-3.30719;
  scores[23][20]=-5.54981;
  scores[23][21]=-1.3609;
  scores[23][22]=-1.42373;
  scores[23][23]=-1.8531;
  scores[23][24]=-1.71212;
  scores[23][25]=-3.62091;
  scores[23][26]=-2.00287;
  scores[23][27]=-5.06782;
  scores[23][28]=-1.83339;
  scores[23][29]=-3.3195;
  scores[24][0]=-100;
  scores[24][1]=-3.11491;
  scores[24][2]=-99;
  scores[24][3]=-1.86442;
  scores[24][4]=-1.58184;
  scores[24][5]=-1.6325;
  scores[24][6]=-1.47564;
  scores[24][7]=-1.66824;
  scores[24][8]=-1.27614;
  scores[24][9]=-2.33409;
  scores[24][10]=-1.473;
  scores[24][11]=-3.28647;
  scores[24][12]=-1.69837;
  scores[24][13]=-3.02973;
  scores[24][14]=-2.44736;
  scores[24][15]=-1.04316;
  scores[24][16]=-1.48877;
  scores[24][17]=-0.832685;
  scores[24][18]=-2.63621;
  scores[24][19]=-1.33394;
  scores[24][20]=-3.97986;
  scores[24][21]=-0.779595;
  scores[24][22]=-0.842747;
  scores[24][23]=-0.886091;
  scores[24][24]=-3.29588;
  scores[24][25]=-3.02377;
  scores[24][26]=-3.08406;
  scores[24][27]=-3.05163;
  scores[24][28]=-2.69788;
  scores[24][29]=-2.91725;
  scores[25][0]=-101.88;
  scores[25][1]=-3.04043;
  scores[25][2]=-100.88;
  scores[25][3]=-1.87754;
  scores[25][4]=-1.1357;
  scores[25][5]=-4.35862;
  scores[25][6]=-3.61584;
  scores[25][7]=-3.52572;
  scores[25][8]=-0.213179;
  scores[25][9]=-3.8393;
  scores[25][10]=-3.63217;
  scores[25][11]=-4.17375;
  scores[25][12]=-0.656173;
  scores[25][13]=-4.69663;
  scores[25][14]=-3.72043;
  scores[25][15]=-2.64647;
  scores[25][16]=-4.27796;
  scores[25][17]=-3.27723;
  scores[25][18]=-1.20316;
  scores[25][19]=-3.8353;
  scores[25][20]=-4.91923;
  scores[25][21]=-2.82389;
  scores[25][22]=-2.90533;
  scores[25][23]=-3.44082;
  scores[25][24]=-2.70708;
  scores[25][25]=-4.01338;
  scores[25][26]=-3.70639;
  scores[25][27]=-4.64227;
  scores[25][28]=-2.1206;
  scores[25][29]=-4.68709;
  scores[26][0]=-100;
  scores[26][1]=-2.55428;
  scores[26][2]=-99;
  scores[26][3]=-1.08345;
  scores[26][4]=-0.68912;
  scores[26][5]=-3.377;
  scores[26][6]=-3.10299;
  scores[26][7]=-2.50285;
  scores[26][8]=-0.71697;
  scores[26][9]=-3.29979;
  scores[26][10]=-4.50007;
  scores[26][11]=-0.913751;
  scores[26][12]=-0.73514;
  scores[26][13]=-4.88156;
  scores[26][14]=-3.37111;
  scores[26][15]=-2.31465;
  scores[26][16]=-2.65165;
  scores[26][17]=-1.4345;
  scores[26][18]=-0.882327;
  scores[26][19]=-3.98379;
  scores[26][20]=-5.62547;
  scores[26][21]=-2.29119;
  scores[26][22]=-1.71792;
  scores[26][23]=-2.36328;
  scores[26][24]=-3.32359;
  scores[26][25]=-5.1791;
  scores[26][26]=-3.915;
  scores[26][27]=-5.32478;
  scores[26][28]=-2.58215;
  scores[26][29]=-4.62177;
  scores[27][0]=-101.153;
  scores[27][1]=-2.13371;
  scores[27][2]=-100.153;
  scores[27][3]=-1.02233;
  scores[27][4]=-1.35054;
  scores[27][5]=-3.81865;
  scores[27][6]=-1.22729;
  scores[27][7]=-4.48766;
  scores[27][8]=-1.08149;
  scores[27][9]=-2.86183;
  scores[27][10]=-4.96478;
  scores[27][11]=-2.12814;
  scores[27][12]=-1.065;
  scores[27][13]=-4.78869;
  scores[27][14]=-5.08972;
  scores[27][15]=-3.51762;
  scores[27][16]=-3.19762;
  scores[27][17]=-3.83444;
  scores[27][18]=-2.21756;
  scores[27][19]=-0.423837;
  scores[27][20]=-4.13548;
  scores[27][21]=-3.75393;
  scores[27][22]=-3.50238;
  scores[27][23]=-0.686649;
  scores[27][24]=-1.75715;
  scores[27][25]=-2.4994;
  scores[27][26]=-3.20323;
  scores[27][27]=-2.98478;
  scores[27][28]=-2.51414;
  scores[27][29]=-4.13552;
  scores[28][0]=-100;
  scores[28][1]=-1.17152;
  scores[28][2]=-99;
  scores[28][3]=-0.135855;
  scores[28][4]=-1.63764;
  scores[28][5]=-3.10547;
  scores[28][6]=-2.42022;
  scores[28][7]=-2.69172;
  scores[28][8]=-1.25025;
  scores[28][9]=-3.67799;
  scores[28][10]=-3.26177;
  scores[28][11]=-3.58231;
  scores[28][12]=-1.60032;
  scores[28][13]=-4.2312;
  scores[28][14]=-3.52681;
  scores[28][15]=-2.4869;
  scores[28][16]=-2.00953;
  scores[28][17]=-2.56838;
  scores[28][18]=-1.73506;
  scores[28][19]=-2.13354;
  scores[28][20]=-5.54406;
  scores[28][21]=-2.30754;
  scores[28][22]=-1.48296;
  scores[28][23]=-2.74356;
  scores[28][24]=-2.34259;
  scores[28][25]=-3.92169;
  scores[28][26]=-2.82772;
  scores[28][27]=-4.53641;
  scores[28][28]=-3.0594;
  scores[28][29]=-3.13053;
  scores[29][0]=-100;
  scores[29][1]=-2.14408;
  scores[29][2]=-99;
  scores[29][3]=-1.00676;
  scores[29][4]=-0.648474;
  scores[29][5]=-1.61957;
  scores[29][6]=-2.92492;
  scores[29][7]=-2.7937;
  scores[29][8]=-0.529466;
  scores[29][9]=-3.05542;
  scores[29][10]=-2.77053;
  scores[29][11]=-1.70079;
  scores[29][12]=-0.855095;
  scores[29][13]=-4.02901;
  scores[29][14]=-2.72142;
  scores[29][15]=-1.99266;
  scores[29][16]=-2.50566;
  scores[29][17]=-2.08189;
  scores[29][18]=-1.21752;
  scores[29][19]=-2.3707;
  scores[29][20]=-3.3855;
  scores[29][21]=-2.88305;
  scores[29][22]=-2.3803;
  scores[29][23]=-3.20569;
  scores[29][24]=-1.42107;
  scores[29][25]=-2.83457;
  scores[29][26]=-3.14228;
  scores[29][27]=-4.68031;
  scores[29][28]=-1.62899;
  scores[29][29]=-1.57262;
};