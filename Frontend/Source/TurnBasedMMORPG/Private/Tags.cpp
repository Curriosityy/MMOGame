#include "Tags.h"

namespace MMOGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SetDestination_Click, "InputTag.SetDestination.Click");

	//Those tags are not bound to specific button, fired from code
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Interaction, "InputTag.Interaction");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Interaction_Attack, "InputTag.Interaction.Attack");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Interaction_MoveToClicked, "InputTag.Interaction.MoveToClicked");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggle, "InputTag.Toggle");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggle_Resting, "InputTag.Toggle.Resting");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld, "InputTag.MustBeHeld");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Event, "InputTag.Event");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Event_Ability, "InputTag.Event.Ability");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Event_Ability_1, "InputTag.Event.Ability.1");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Event_Ability_2, "InputTag.Event.Ability.2");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Event_Ability_3, "InputTag.Event.Ability.3");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Event_Ability_4, "InputTag.Event.Ability.4");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Event_Ability_5, "InputTag.Event.Ability.5");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Event_Ability_6, "InputTag.Event.Ability.6");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Event_AddAbility, "InputTag.Event.AddAbility");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Event_RemoveAbility, "InputTag.Event.RemoveAbility");
	//Player
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability, "Player.Ability");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Resting, "Player.Ability.Resting");

	UE_DEFINE_GAMEPLAY_TAG(Player_Status, "Player.Status");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Premium, "Player.Status.Premium");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Resting, "Player.Status.Resting");

	UE_DEFINE_GAMEPLAY_TAG(Player_Event, "Player.Event");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_MoveToLocation, "Player.Event.MoveToLocation");

	//Monster
	UE_DEFINE_GAMEPLAY_TAG(Monster_Ability, "Monster.Ability");

	UE_DEFINE_GAMEPLAY_TAG(Monster_Status, "Monster.Status");

	UE_DEFINE_GAMEPLAY_TAG(Moster_Event, "Monster.Event");
	//Shared
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability, "Shared.Ability");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Slot, "Shared.Ability.Slot");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Slot_1, "Shared.Ability.Slot.1");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Slot_2, "Shared.Ability.Slot.2");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Slot_3, "Shared.Ability.Slot.3");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Slot_4, "Shared.Ability.Slot.4");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Slot_5, "Shared.Ability.Slot.5");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Slot_6, "Shared.Ability.Slot.6");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_PlayQueue, "Shared.Ability.PlayQueue");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Status, "Shared.Status");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_CurrentTurn, "Shared.Status.CurrentTurn");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Battle, "Shared.Status.Battle");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_AbilityGranted, "Shared.Status.AbilityGranted");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Death, "Shared.Status.Death");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Dodged, "Shared.Status.Dodged");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Event, "Shared.Event");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_TryAddAbility, "Shared.Event.TryAddAbility");

	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller, "Shared.SetByCaller");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_SkillDamage, "Shared.SetByCaller.SkillDamage");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_WeaponDamage_Low, "Shared.SetByCaller.WeaponDamage.Low");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_WeaponDamage_Max, "Shared.SetByCaller.WeaponDamage.Max");

	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_SpellDamageMultiplier_Strength,
	                       "Shared.SetByCaller.SpellDamageMultiplier.Strength");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_SpellDamageMultiplier_Dexterity,
	                       "Shared.SetByCaller.SpellDamageMultiplier.Dexterity");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_SpellDamageMultiplier_Intelligence,
	                       "Shared.SetByCaller.SpellDamageMultiplier.Intelligence");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_SpellDamageMultiplier_Wisdom,
	                       "Shared.SetByCaller.SpellDamageMultiplier.Wisdom");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_SpellDamageMultiplier_Faith,
	                       "Shared.SetByCaller.SpellDamageMultiplier.Faith");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_SpellDamageMultiplier_Charisma,
	                       "Shared.SetByCaller.SpellDamageMultiplier.Charisma");

	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_HitChance_Base, "Shared.SetByCaller.HitChance.Base");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_HitChance_Weapon, "Shared.SetByCaller.HitChance.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_SkillMultiplier, "Shared.SetByCaller.SkillMultiplier");

	//CommunicationLine
	UE_DEFINE_GAMEPLAY_TAG(Message, "Message");
	UE_DEFINE_GAMEPLAY_TAG(Message_Battle, "Message.Battle");
	UE_DEFINE_GAMEPLAY_TAG(Message_Battle_OnAbilityClicked, "Message.Battle.OnAbilityClicked");
	UE_DEFINE_GAMEPLAY_TAG(Message_OnQueueRefreshed, "Message.OnQueueRefreshed");
	UE_DEFINE_GAMEPLAY_TAG(Message_OnBarUpdated, "Message.OnBarUpdated");
}
