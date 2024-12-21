#include "pch.h"

static ModelInfo* QoliPlaneMdl = nullptr;

bool CheckIfSonicPlane(NJS_MODEL_SADX* model) {
	return QoliPlaneMdl->getlabel(model) != "";
}

void __cdecl TornadoCallBack(NJS_MODEL_SADX* model, int blend, int idk) {
	NonStaticFunctionPointer(void, sub_407FC0, (NJS_MODEL_SADX*, int), 0x407FC0);

	// If the currently drawn model is part of QOLI_PLANE, we use the character's texlist instead
	if (CheckIfSonicPlane(model)) {
		NJS_TEXLIST* tex_orig = CurrentTexList;

		njSetTexture(&SONIC_TEXLIST);
		sub_407FC0(model, blend);
		njSetTexture(tex_orig);
	}
	else {
		sub_407FC0(model, blend);
	}
}

void njAction_Queue_Tornado(NJS_ACTION* action, float frame, QueuedModelFlagsB flags) {
	DisplayAnimationFrame(action, frame, flags, 0.0, TornadoCallBack);
}

void TornadoQoli_init(const HelperFunctions& helperFunctions) {
	ModelInfo* mdl = new ModelInfo(helperFunctions.GetReplaceablePath("system\\QOLI_PLANE.sa1mdl"));

	if (mdl->getformat() == ModelFormat_Basic) {
		QoliPlaneMdl = mdl;

		// We only replace Sonic's part of the plane
		Tornado1_Object.child->sibling->sibling->sibling->child = QoliPlaneMdl->getmodel();
		Tornado2Before_Object.child->sibling->sibling->child = QoliPlaneMdl->getmodel();
		Tornado2Change_Object.child->sibling->sibling->sibling->sibling->child = QoliPlaneMdl->getmodel();

		// Hack to use our own texture for Qoli's part of the plane, allowing compatibility with dc mods.
		WriteCall((void*)0x62753A, njAction_Queue_Tornado);
	}
	else {
		PrintDebug("[Qoli the Fox] Cannot open \"QOLI_PLANE.sa1mdl\".\n");
	}
}