using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using ProjetNichoir.Data;
using ProjetNichoir.Models;

namespace ProjetNichoir.Controllers
{
    public class HomeController : Controller
    {
        //private readonly ApplicationDbContext _context;

        //public HomeController(ApplicationDbContext context)
        //{
        //    _context = context;
        //}
        public IActionResult Index()
        {

            //Nichoir nichoirs = new Nichoir
            //{
            //    nom = "test",
            //    date_ajout = DateTime.Now,
            //    description = "description",
            //    emplacement = "test de babar",
            //    resolution_camera = "2mp",
            //    statut_batterie = 10,
            //    statut_led_ir = true,
            //    statut_pir = true,

            //};
            //_context.Set<Nichoir>().Add(nichoirs);
            //_context.SaveChanges();

            //Capture captures = new Capture
            //{
            //    nichoir = nichoirs,
            //    batterie = 20,
            //    chemin_image = "test",
            //    resolution = "3mp",
            //    taille_image = 2,
            //    date_capture = DateTime.Now,
            //};

            //_context.Set<Capture>().Add(captures);
            //_context.SaveChanges();
            return View();
        }

        public IActionResult Privacy()
        {
            return View();
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}
