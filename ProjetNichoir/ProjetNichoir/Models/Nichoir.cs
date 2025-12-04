using System.ComponentModel.DataAnnotations;

namespace ProjetNichoir.Models
{
    public class Nichoir
    {
        [Key]
        public int id_nichoir { get; set; }

        [Required]
        [StringLength(50, ErrorMessage = "Le nom doit contenir maximum 50 caractères.")]
        public string nom { get; set; }

        [StringLength(50, ErrorMessage = "L'emplacement doit contenir maximum 50 caractères.")]
        public string? emplacement { get; set; }

        [StringLength(255)]
        public string? description { get; set; }

        public DateTime date_ajout { get; set; } = DateTime.Now;

        public int? statut_batterie { get; set; }

        public bool? statut_pir { get; set; }

        public bool? statut_led_ir { get; set; }

        [StringLength(50)]
        public string? resolution_camera { get; set; }

        // Relation 1 -> Many
        public List<Capture>? Captures { get; set; }
    }
}
