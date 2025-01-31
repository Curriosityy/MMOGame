﻿using OWSData.Models.StoredProcs;
using OWSData.Models.Tables;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OWSData.Models.Composites
{
    public class CharacterAndCustomData
    {

        public Guid? UserSessionGuid { get; set; }
        public GetCharByCharName CharacterData { get; set; }
        public List<CustomCharacterDataDTO> CustomCharacterDataRows { get; set; }
}
}
