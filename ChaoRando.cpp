#include "stdafx.h"
#include "ChaoRando.h"


ChaoDataBaseGap saveChao;
const int chaoCNT = 570;
char* chao[570] = { "mindacos", "Exant","MainMemory" ,"Mekhialtey02" , "_Gimmick", "_Houston", "0rbis", "1219nekogami", "2D", "44moth", "A_Bowl_Of_Cereal", "a_moustache", "aaaa", "AbsentSR", "acs13123", "Aero_Trigger", "Æzir", "afrogamer2660", "Aggressively Medium", "aguedouf", "AhoyKMS", "aioproject", "Air_iq", "akureikorineko", "Allegro", "Altairan", "AmberCyprian", "Ambloops", "Americanchoirboy", "andzura", "anthonyjuice", "AphexArcade", "Aquova", "AReytoRemember", "Argick", "Armageddun", "ArmorySons", "Aruki", "ASINISTERTACO", "asparcel", "Asterisk254", "Asylix", "Atircerile", "auraace", "Avento128bits", "AxlThunder", "Badlex727", "BarelyFunctional", "Basouification", "Baylee", "bbqsauz", "Bikee", "BillPzc", "Birdy", "Bizkit", "Blatan", "BlazinZzetti", "BlitzBlatt", "Bluelightdimming", "BMW0401_2", "bony", "bonzi77", "Boohead86", "BoostedBandCamp", "bowlercaptain", "brassmonkejr", "Brian_pso", "Brodyzera", "BrokenArthritis", "buckethead222", "Budmin", "BuffaloPrime", "Burningskull123", "Bushiidox", "BUxSteven", "CaitlynMarv", "canariabird", "Captsamerica", "Casusby", "CCNeverender", "Centari", "Cereth", "chainchump", "chanman", "ChaoticChao", "Chaoz163", "CharamelMou", "ChelseyxLynn", "chronoon", "Chucat", "Ckarl_Bobadine", "ClaireSV", "Classic", "Cleekoh", "Clumzy_Chao24", "Lexi", "Condus", "ConkerBandicoot", "Conklestothemax", "cookiepocalypse", "coolcolegamer", "CowTech", "CptPuff", "Cream147", "Cricketdx", "Crispian", "CriticalCyd", "Cryphon", "CrystalChaos", "ctagent", "CuukiesODeath", "CyanideKry", "cybersonicstarzx655", "dabbingjesus", "Dage4", "Daisukemara", "Danidesu", "Darkaria21", "Darkpr0", "Dartanian881", "Dawngaward", "DearmondzFTW", "Deku_sr", "DemotedStaff", "Desura", "Dfesfsfs", "DhrGR", "Diabuk", "DieserFMG", "DiGG3rZ", "dimes", "DirtyDillers", "disconnectoid", "DizzyPrime", "DjShovel", "Dnyceboy", "DolphinDasher", "donniesmithers", "Dorocco", "Draco655", "Drakodan", "drasamii", "Dreamtora", "Drewbiie", "DRGNDrags123", "drminus", "DrPhysic", "Drum", "Drunk_Loli", "DRX-Vector", "drywalleater69", "Dunham", "dusty_pecker", "Eat4thelolz", "EdwardBottle", "ElectricMiles", "EliteCarnage", "Emerauld", "Emerldd", "emerua", "enigma20", "EnPassant", "enu", "Epicfrogskater", "ethmar", "EverlastingSaint", "eXceL", "F_aux", "failgames100", "Failinator", "Faleroth", "FallenFury777", "fastlikesanic", "FierceClash", "FierceFrankie", "FiniteChaos", "Fivavoa", "FloppyDisk", "Flowleyd", "Fomako", "ford373", "foxdra", "Freefall", "FriskyHarambe", "Frokenok", "Frozer", "FuryRising", "g00gly0eyes", "Gailardia", "Gamercal", "Gc4ever4001", "Geno", "Gerp", "Ghoul02", "Ghoulston", "Godly79", "Gold", "Goldenboy", "Goldwolf11", "Gpro", "GrandStarYoshi", "Graphox", "GrayMagicGamma", "Greg", "Grievenomore", "grumblebundle", "Gupply", "Gurdill63", "GuyStreamsStuff", "Gvoltt", "Hawkrex", "Hazel", "Hephlex", "heytallman", "Homes1ck", "Hoopy", "Hoopyhoop1", "Hugasaurus", "Hughmanphist", "HypeMaster2020", "iambpburke", "icedog158", "Iden", "IDGeek121", "iexrrr", "Indextic", "iNeoRetro", "IrregularZero", "Ishmon", "IsleDelfino", "ITLAU", "IvanGS", "Ivegotdatfeel", "Izayoi83", "Jackwitherell", "Jailkat7", "jamception", "Jatenk", "JazzSpeedruns", "jbird", "JBuzzyBee", "Jel", "jellyfishswimmer", "JerKro", "JetSethRadio", "JHobz", "Joedor", "Joeey", "Joerunner", "jolteontrainer", "JonSuperEmerald", "Jordiebee", "Joshifire", "Jpaintrain", "jrk9", "jtnoble321", "Justalot123", "Justgoodpop", "jw13", "Keefyy", "Keeta", "Keewy", "kendallswan", "Keoneon", "Kheartz", "Kimmstaa", "Kimshi", "Kingshadowclock", "kinkycadence", "KinokoJules", "koinu93", "Kurayami", "Kyonexe", "Kytes", "Kyyrie", "Lambo", "LaughTrack", "Leetus", "Leeyuna", "Leif26", "Lergi", "Lewisb99", "Lightning55", "Linkkiro", "Liquid_Bosscelot", "LittleBigness", "Lonewo1f001", "Lordfartamor", "Lotuski24", "LuraxThunder", "Mar", "Markhest", "markusman64ds", "Marshy", "Marumiju", "Mastakirby", "Master-Kuruk", "MasterWaffled", "Matthewfupp", "Mattmurpz", "Mayakanai65", "mcshuggets", "Mecklemisuer", "Matoi", "MelonSpeedruns", "Meltrs", "Menstilo", "MessMyPants", "MetalGlennSolid", "MetroidMaster", "Midboss", "MidnightRambler", "mie_Dax", "Minamiyo", "Mitorequiem", "Mitsuray", "ModifiedMonkee", "Moeter", "Movellandrone", "Mr_Mango", "Mr.Tortellini", "MrDarkIce", "Mrgenericname", "Mrhappyismissing", "MrSanderss", "MrWoofies", "MyPairOfSocks", "MysticRebel", "Napuc", "Nathacsa", "nebbii", "Neptune", "Nerfned2000", "NeroBron", "NEVERDOORS", "Nick902", "Nickireda", "Nightmare47", "NiGHTOPiAN", "Niisoks", "Nimputs", "Nineball", "ninjahenrik", "NiNJaOwNeD", "Ninjembro", "NoThisIsStupider", "Okam", "OnVar", "OSC", "OutrageousJosh", "Oxtane", "Ozzi9816", "Parameter152", "Parkraft123", "Patafoin", "Paulie9990", "Pearstrike", "Pepeye", "Perdonium", "petrie911", "phantoms83", "Phat-Boss", "Phijkchu_tdk", "Pika_choo1", "Pikapals", "piner", "Pixelle", "PKMNtrainerGian", "Pokemanaphy", "Pokestuck33", "Prahaha", "price211066", "Primzi", "PrinceKaro", "Prinny", "PrismaticBlack", "Project", "Proto", "prouds1lver", "Psyknux", "PsyMar", "puchiedarcy", "Puddinghouse", "R3FR4G", "racksblue", "Ragecat", "Raikou", "RaiuPlays", "Rajaxx", "Randomguy55", "RandyBumgardener", "Rapture", "raqibmarvelous", "Ravaildisney", "Ravel", "Razzz", "redsky764", "relik9r", "Renegade522", "RetroRuns", "rezephos", "Rhapsody", "RingEnergy", "Ringrush", "RinKagamine1", "RjassoA", "rodyonce", "SaimeZX", "saintsfighter", "SalmonBuffalo", "Samitian", "SanicSpaceParty", "Savac", "Sayuri", "Sazabi0093", "SB737", "Scamper", "SCT", "Sekanor", "Selphos", "Senzura", "Seraphim", "Shadow2701", "ShadowCero", "ShadowFrost", "Shady_", "shamana", "Shanekilz", "shibakee", "ShiningFace", "SMB", "Silo_Simon", "SimLola661", "simpleton216", "SimplicityWalrus", "Sircharles", "skull_kid_64", "SlickEvan", "Slurm_king", "Snodeca", "Son1cgu1tar", "Sonicku", "Sonikku", "Sora", "SpaceBroJakob", "spades", "Spark3", "Sparkky", "spikevegeta", "spinful", "SpookySpeedruns", "squidtepig", "SqwareEcks", "SSBMstuff", "SSJPichu", "Stevewontleave", "StickFigureVector", "Stirliing", "stllr", "Stonie", "super_alice", "super_sanic123", "SuperDennyBoi", "SuperNerdMiles", "SuperSonic", "Supra", "surfingpikachu", "Suzuru", "Swaaggyy", "SwearImNotAWeeb", "Tallcat", "Talon2461", "Tandom_gamer1", "Tape1", "Techiyo", "TehCherokee", "Tekkie", "Tenacity", "The_Gods", "the0nlykyd", "TheAlphaDolphin", "TheBricktator", "Thecobra931", "TheJokernaut", "theJUICE", "TheKiwiTurtle", "themanual768", "thepuddingfighter", "TheRealMrJangle", "Therio", "TheStrangeMentlegen", "Theunexpected5", "thewaytodawnnn", "Thorn", "Tigerkyle1", "Tikal", "Tikwi", "TiltedStilts", "Timic", "TimpZ", "TJRedeemer", "togain", "tolvengyr", "Tommy", "Tommyspud", "TonesBalones", "toon_rito", "Torpy", "Touch", "ToxicFaker", "Traitor", "Treasure", "Tricolour", "Trix", "trunkynugget", "Ts4ever1201", "TwinkieSWF", "TwoferTuesday", "tyhill111", "Tylenol", "undeadforce22", "Unrealodin", "UnsupervisedFun", "Usiku", "Valioa", "Vark", "Venombyte", "ventiyordle", "Viblosh", "Video2gud", "Vilsol", "Vixuzen", "Vynneve", "WaddleDaisy", "WarpWhistle", "Weegeezv", "welldooder64", "welsar55", "Werey", "Whizzy_the_Elephant", "windssunrise1", "WindsSunrise1", "Wolfii", "Wolfluke", "woofpack", "Wooguy78", "wosige", "Wub", "x10power", "Xallesii", "Xelonious", "xGonzo", "xNose", "Xonos117", "Yes", "Yesjong", "YESR", "Yesthrough", "yoshifan", "yoshipartout", "Yoshis2ndcousin", "yuuutaaaapoonnn", "Zackoon49", "Zeldrak", "ZellnuuEon", "Zeph", "Zodiac92", "Zombiemaster", "Zyldara", "Zync" };



byte encodeLetter(char a) {
	switch (a) {
	case '-':
		return 0x0D;
	case '_':
		return 0x3F;
	case '0':
		return 0x10;
	case '1':
		return 0x11;
	case '2':
		return 0x12;
	case '3':
		return 0x13;
	case '4':
		return 0x14;
	case '5':
		return 0x15;
	case '6':
		return 0x16;
	case '7':
		return 0x17;
	case '8':
		return 0x18;
	case '9':
		return 0x19;
	case 'A':
		return 0x21;
	case 'B':
		return 0x22;
	case 'C':
		return 0x23;
	case 'D':
		return 0x24;
	case 'E':
		return 0x25;
	case 'F':
		return 0x26;
	case 'G':
		return 0x27;
	case 'H':
		return 0x28;
	case 'I':
		return 0x29;
	case 'J':
		return 0x2A;
	case 'K':
		return 0x2B;
	case 'L':
		return 0x2C;
	case 'M':
		return 0x2D;
	case 'N':
		return 0x2E;
	case 'O':
		return 0x2F;
	case 'P':
		return 0x30;
	case 'Q':
		return 0x31;
	case 'R':
		return 0x32;
	case 'S':
		return 0x33;
	case 'T':
		return 0x34;
	case 'U':
		return 0x35;
	case 'V':
		return 0x36;
	case 'W':
		return 0x37;
	case 'X':
		return 0x38;
	case 'Y':
		return 0x39;
	case 'Z':
		return 0x3A;
	case ' ':
		return 0x5F;
	case 'a':
		return 0x41;
	case 'b':
		return 0x42;
	case 'c':
		return 0x43;
	case 'd':
		return 0x44;
	case 'e':
		return 0x45;
	case 'f':
		return 0x46;
	case 'g':
		return 0x47;
	case 'h':
		return 0x48;
	case 'i':
		return 0x49;
	case 'j':
		return 0x4A;
	case 'k':
		return 0x4B;
	case 'l':
		return 0x4C;
	case 'm':
		return 0x4D;
	case 'n':
		return 0x4E;
	case 'o':
		return 0x4F;
	case 'p':
		return 0x50;
	case 'q':
		return 0x51;
	case 'r':
		return 0x52;
	case 's':
		return 0x53;
	case 't':
		return 0x54;
	case 'u':
		return 0x55;
	case 'v':
		return 0x56;
	case 'w':
		return 0x57;
	case 'x':
		return 0x58;
	case 'y':
		return 0x59;
	case 'z':
		return 0x5A;
	default:
		return 0x5F;
	}
}

ChaoDataBaseGap randomizeChao(ChaoDataBaseGap cdb) {

	ChaoGardensUnlocked = 255;
	for (int i = 0; i < 32; i++) {
		BlackMarketSlots[i].Category = 1;
		BlackMarketSlots[i].Type = rand() % 68;
	}


	saveChao = cdb;

	saveChao.Color = rand() % 256;
	saveChao.Shiny = rand() % 5;
	if (saveChao.Shiny == 4) saveChao.Shiny = 1;
	else saveChao.Shiny = 0;
	if (saveChao.Shiny) {
		saveChao.MonotoneHighlights = rand() % 5;
		if (saveChao.MonotoneHighlights) saveChao.MonotoneHighlights = 1;
		else saveChao.MonotoneHighlights = 0;
	}
	else {
		saveChao.MonotoneHighlights = rand() % 2;
		saveChao.Texture = rand() % 110;
	}
	
	


	int modelNo = rand() % 69;
	if (modelNo > 4) modelNo = 0;
	saveChao.BodyType = modelNo;
	if (modelNo == 3) {
		int animal = rand() % 21;
		if (animal == 2) animal = 20;
		saveChao.BodyTypeAnimal = animal;
	}


	string name(chao[rand() % chaoCNT]);
	int len = 7;
	if (name.length() < 7) len = name.length();
	for (int i = 0; i < len; i++) {
		saveChao.Name[i] = encodeLetter(name[i]);
	}


	saveChao.RunLevel = rand() % 99 + 1;
	saveChao.FlyLevel = rand() % 99 + 1;
	saveChao.SwimLevel = rand() % 99 + 1;
	saveChao.PowerLevel = rand() % 99 + 1;
	saveChao.StaminaLevel = rand() % 99 + 1;
	saveChao.LuckLevel = rand() % 99 + 1;
	saveChao.IntelligenceLevel = rand() % 99 + 1;
	//saveChao.Happiness = rand() % 201 - 100;
	saveChao.Type = rand() % 25 + 1;
	//saveChao.Alignment = rand() % 3 - 1;
	saveChao.FlyGrade = rand() % 6;
	saveChao.RunGrade = rand() % 6;
	saveChao.SwimGrade = rand() % 6;
	saveChao.PowerGrade = rand() % 6;
	saveChao.StaminaGrade = rand() % 6;
	saveChao.LuckGrade = rand() % 256;
	saveChao.IntelligenceGrade = rand() % 256;

	int lvlStat = rand() % 20 + 13;
	saveChao.FlyStat = saveChao.FlyLevel * 6 * (saveChao.FlyGrade + 1);
	saveChao.RunStat = saveChao.RunLevel *lvlStat* (saveChao.RunGrade + 1);
	saveChao.PowerStat = saveChao.PowerLevel * 6 * (saveChao.PowerGrade + 1);
	saveChao.SwimStat = saveChao.SwimLevel *lvlStat * (saveChao.SwimGrade + 1);
	saveChao.StaminaStat = saveChao.StaminaLevel *lvlStat * (saveChao.StaminaGrade + 1);
	saveChao.LuckStat = saveChao.LuckLevel *lvlStat * (saveChao.LuckGrade + 1);
	saveChao.IntelligenceStat = saveChao.IntelligenceLevel * 6 * (saveChao.IntelligenceGrade + 1);


	if (rand() % 2 == 0) saveChao.PowerRun = rand() % 3 - 1;
	else saveChao.FlySwim = rand() % 3 - 1;

	saveChao.Lifespan = 200;
	saveChao.EvolutionProgress = rand() % 13 / 10.0;
	//saveChao.field_190[0x4E4] |= 2;
	//saveChao.Garden = 1;
	cdb = saveChao;
	return saveChao;
}


ChaoType intToType(int i) {
	ChaoType ar[] = {
	ChaoType_Good,
	ChaoType_Bad,
	ChaoType_Neutral_Normal,
	ChaoType_Hero_Normal,
	ChaoType_Dark_Normal,
	ChaoType_Neutral_Swim,
	ChaoType_Hero_Swim,
	ChaoType_Dark_Swim,
	ChaoType_Neutral_Fly,
	ChaoType_Hero_Fly,
	ChaoType_Dark_Fly,
	ChaoType_Neutral_Run,
	ChaoType_Hero_Run,
	ChaoType_Dark_Run,
	ChaoType_Neutral_Power,
	ChaoType_Hero_Power,
	ChaoType_Dark_Power,
	ChaoType_Neutral_Chaos,
	ChaoType_Hero_Chaos,
	ChaoType_Dark_Chaos,
	ChaoType_Tails,
	ChaoType_Knuckles,
	ChaoType_Amy };

	return ar[i];

}

ChaoData* randomizeCarriedChao(ChaoData* cdb) {



	cdb->data.Color = rand() % 256;
	cdb->data.Shiny = rand() % 2;
	cdb->data.MonotoneHighlights = rand() % 2;
	cdb->data.Texture = rand() % 110;


	string name(chao[rand() % chaoCNT]);
	int len = 7;
	if (name.length() < 7) len = name.length();
	for (int i = 0; i < len; i++) {
		cdb->data.Name[i] = encodeLetter(name[i]);
	}
	
	
	cdb->data.Type = intToType(rand() % 25 + 1);
	

	if (rand() % 2 == 0) cdb->data.PowerRun = rand() % 3 - 1;
	else cdb->data.FlySwim = rand() % 3 - 1;

	cdb->data.Lifespan = 200;
	cdb->data.EvolutionProgress = rand() % 13 / 10.0;

	//cdb.data.Garden = 1;

	return cdb;
}


ChaoDataBaseGap maxChao(ChaoDataBaseGap cdb) {



	saveChao = cdb;

	saveChao.RunLevel = 0;
	saveChao.FlyLevel = 0;
	saveChao.SwimLevel = 0;
	saveChao.PowerLevel = 0;
	saveChao.StaminaLevel = 99;
	saveChao.LuckLevel = 0;
	saveChao.IntelligenceLevel = 99;
	//saveChao.Happiness = rand() % 201 - 100;
	//saveChao.Type = 2 + (3 * (rand() % 8));
	//saveChao.Alignment = rand() % 3 - 1;
	saveChao.FlyGrade = 5;
	saveChao.RunGrade = 5;
	saveChao.SwimGrade = 5;
	saveChao.PowerGrade = 5;
	saveChao.StaminaGrade = 5;
	saveChao.LuckGrade = 255;
	saveChao.IntelligenceGrade = 255;

	//int lvlStat = rand() % 20 + 10;
	saveChao.FlyStat = 3600;
	saveChao.RunStat = 9999;
	saveChao.PowerStat = 3600;
	saveChao.SwimStat = 9999;
	saveChao.StaminaStat = 65535;
	saveChao.LuckStat = 3000;
	saveChao.IntelligenceStat = 3000;
	//saveChao.PowerRun = rand() % 500 - 250;
	//saveChao.FlySwim = rand() % 500 - 250;
	//saveChao.Lifespan = 200;
	//saveChao.EvolutionProgress = rand() % 13 / 10.0;
	//saveChao.Garden = 1;
	cdb = saveChao;
	return saveChao;
}


ChaoDataBaseGap animalChao(ChaoDataBaseGap cdb) {
	saveChao = cdb;

	saveChao.SA2BArmType = rand() % 22 - 1;
	saveChao.SA2BEarType = rand() % 22 - 1;
	saveChao.SA2BForeheadType = rand() % 22 - 1;
	saveChao.SA2BHornType = rand() % 22 - 1;
	saveChao.SA2BLegType = rand() % 22 - 1;
	saveChao.SA2BTailType = rand() % 22 - 1;
	saveChao.SA2BWingType = rand() % 22 - 1;
	saveChao.SA2BFaceType = rand() % 22 - 1;

	int r = rand() % 6;
	if (r == 0) saveChao.Headgear = rand() % 56 + 15;
	else if (r == 1) saveChao.Headgear = rand() % 16;
	else saveChao.Headgear = 0;

	cdb = saveChao;
	return saveChao;
}
void printChao(RaceBotData c) {
	string s = "";
		s  += "somestatthing: ";
	s += std::to_string(c.someStatThing);
	s += " stat: " + std::to_string(c.stat);
	s+= " swim " + std::to_string(c.swim);
	s+= " s3a " + std::to_string(c.field_3A);
	s+= " fly " + std::to_string(c.fly);
	s+= " s3E " + std::to_string(c.field_3E);
	s+= " run " + std::to_string(c.run);
	s+= " s42 " + std::to_string(c.field_42);
	s+= " power " + std::to_string(c.power);
	s+= " s46 " + std::to_string(c.field_46);

	PrintDebug(s.c_str());
}
RaceBotData randomRaceChao(int idx, RaceBotData rChao) {
	rChao.typeRandom = rand() % 27 + 2;
	rChao.BallType = rand() % 3;
	rChao.Color = rand() % 256;
	rChao.Texture = rand() % 110;
	int r = rand() % 6;
	if (r == 0) rChao.HeadGear = rand() % 56 + 15;
	else if (r == 1) rChao.HeadGear = rand() % 16;
	else rChao.HeadGear = 0;
	rChao.ShinyMonotone = rand() % 2;
	rChao.Medal = rand() % 16;
	rChao.AlignmentBase = 1.2;
	//rChao.stat *= idx;
	//printChao(rChao);
	if (idx > 0) {
		if (rChao.someStatThing == 1) {
			idx *= 100;
			rChao.swim += idx;
			rChao.run += idx;
			rChao.fly += idx;
			rChao.power += idx;
		}
		else {
			rChao.stat += idx * 100;
		}
	}
	//if (rChao.power > 1000 || rChao.power < 0) rChao.power = 1000;
	//rChao.stamina *= idx;
	//rChao.luck = 3000;
	//rChao.intelligence = 3000;
	rChao.animalpartRandom = rand() % 8;
	rChao.eyeRandom = rand() % 14;
	rChao.mouthRandom = rand() % 16;

	return rChao;
}

struct_a1R randomKarateChao(int idx,struct_a1R kChao) {
	//Body & Color//

	kChao.ChaoType = rand() % 0x17 + 2;
	kChao.EyeType = rand() % 14;
	kChao.BallType = rand() % 3;
	kChao.Color = rand() % 256;
	kChao.Texture = rand() % 110;
	kChao.MouthType = rand() % 16;
	int r = rand() % 6;
	if (r == 0) kChao.Headgear = rand() % 56 + 15;
	else if (r == 1) kChao.Headgear = rand() % 16;
	else kChao.Headgear = 0;
	kChao.Monotone = rand() % 2;
	kChao.Shiny = rand() % 2;
	kChao.Medal = rand() % 16;

	//Random Animal Parts//
	if(rand()%3 == 0) kChao.SA2BArmType = rand()%22-1;
	if (rand() % 3 == 0 )kChao.SA2BEarType = rand() % 22-1;
	if (rand() % 3 == 0) kChao.SA2BForeheadType = rand() % 22-1;
	if (rand() % 3 == 0) kChao.SA2BHornType = rand() % 22-1;
	if (rand() % 3 == 0) kChao.SA2BLegType = rand() % 22-1;
	if (rand() % 3 == 0) kChao.SA2BTailType = rand() % 22-1;
	if (rand() % 3 == 0) kChao.SA2BWingType = rand() % 22-1;
	if (rand() % 3 == 0) kChao.SA2BFaceType = rand() % 22-1;
	

	//Evolutions//
	if (rand() % 2 == 0) kChao.PowerRun = rand() % 3 - 1;
	else kChao.FlySwim = rand() % 3 - 1;
	kChao.Magnitude = rand() % 13 / 10.0;
	

	//Name//
	string name(chao[rand() % chaoCNT]);
	int len = 7;
	if (name.length() < 7) len = name.length();
	for (int i = 0; i < len; i++) {
		kChao.Name[i] = encodeLetter(name[i]);
	}
	

	//Stats//
	/*float mul = idx / 20.0;
	kChao.StatPoints[0] = (mul) * 3600 + rand() % 1000;
	kChao.StatPoints[1] = (mul) * 9999 + rand() % 1000;
	kChao.StatPoints[2] = (mul) * 3600 + rand() % 1000;
	kChao.StatPoints[3] = (mul) * 9999 + rand() % 1000;
	kChao.StatPoints[4] = (mul) * 62000 + rand() % 1000;
	kChao.StatPoints[5] = (mul) * 3600 + rand() % 1000;
	kChao.StatPoints[6] = (mul) * 3600 + rand() % 1000;
	kChao.StatPoints[7] = 0;*/



	return kChao;
}