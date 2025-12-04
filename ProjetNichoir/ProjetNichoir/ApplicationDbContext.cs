using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Internal;
using ProjetNichoir.Models;
using System.Text.RegularExpressions;


namespace ProjetNichoir.Data
{
    public class ApplicationDbContext : DbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        { }

        public DbSet<Nichoir> Nichoirs { get; set; }
        public DbSet<Models.Capture> Captures { get; set; }


        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Models.Capture>()
                .HasOne(c => c.nichoir)
                .WithMany(n => n.Captures)
                .HasForeignKey(c => c.id_nichoir)
                .OnDelete(DeleteBehavior.Cascade);
        }
    }
}
