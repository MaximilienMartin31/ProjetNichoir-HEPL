using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace WebApplication1.Models
{
    public class Capture
    {
        [Key]
        public int id_capture { get; set; }
        public string chemin_image { get; set; }
        public DateTime date_capture { get; set; }
        public int taille_image { get; set; }
        public int batterie { get; set; }
        public string resolution { get; set; }
        public bool favoris { get; set; } // Default 0 en DB
        public virtual ICollection<Album_Capture>? Album_Captures { get; set; } = new List<Album_Capture>();

    }
}
