using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace ProjetNichoir.Models
{
    public class Capture
    {
        [Key]
        public int id_capture { get; set; }

        [ForeignKey("Nichoir")]
        public int id_nichoir { get; set; }

        public Nichoir? nichoir { get; set; }

        [Required]
        [StringLength(255)]
        public string chemin_image { get; set; }

        public DateTime date_capture { get; set; } = DateTime.Now;

        public int? taille_image { get; set; }

        public int? batterie { get; set; }

        [StringLength(50)]
        public string? resolution { get; set; }
    }
}
