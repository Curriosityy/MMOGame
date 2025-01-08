using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Text.Json.Serialization;

namespace OWSData.Models.StoredProcs
{
    public class GetCharByCharName
    {
        public GetCharByCharName()
        {
            IsAdmin = false;
            IsModerator = false;
        }

        public Guid CustomerGuid { get; set; }
        public int CharacterId { get; set; }
        public Guid? UserGuid { get; set; }

        public string Email { get; set; }
        public bool IsAdmin { get; set; }
        public bool IsModerator { get; set; }

        [JsonPropertyName("CharacterName")]
        public string CharName { get; set; }
        public string MapName { get; set; }
        public double X { get; set; }
        public double Y { get; set; }
        public double Z { get; set; }
        public string ServerIp { get; set; }
        public DateTime LastActivity { get; set; }
        public double Rx { get; set; }
        public double Ry { get; set; }
        public double Rz { get; set; }
        public short CharacterLevel { get; set; }
        public int Exp { get; set; }
        public byte Gender { get; set; }
        public int MaxHealth { get; set; }
        public int Health { get; set; }
        public int MaxMana { get; set; }
        public int Mana { get; set; }
        public int Stamina { get; set; }
        public int MaxStamina { get; set; }
        public int Strength { get; set; }
        public int Dexterity { get; set; }
        public int Intelligence { get; set; }
        public int Wisdom { get; set; }
        public int Faith { get; set; }
        public int Charisma { get; set; }
        public int MaxAbilityPoints { get; set; }
        public double Alignment { get; set; }
        public string DefaultPawnClassPath { get; set; }
        public bool IsInternalNetworkTestUser { get; set; }
        public int ClassId { get; set; }
        public string BaseMesh { get; set; }
        public int Port { get; set; }
        public int MapInstanceID { get; set; }
        public string ClassName { get; set; }
    }
}
