﻿// ====================================================
//
// 
// ====================================================

using System;
using System.Linq;


namespace BeesKnees.ViewModels
{
    public class OrderViewModel
    {
        public int Id { get; set; }
        public decimal Discount { get; set; }
        public string Comments { get; set; }
    }
}