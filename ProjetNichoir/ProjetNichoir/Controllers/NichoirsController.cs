using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using ProjetNichoir.Data;
using ProjetNichoir.Models;

namespace ProjetNichoir.Controllers
{
    public class NichoirsController : Controller
    {
        private readonly ApplicationDbContext _context;

        public NichoirsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: Nichoirs
        public async Task<IActionResult> Index()
        {
            return View(await _context.Nichoirs.ToListAsync());
        }

        // GET: Nichoirs/Details/5
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var nichoir = await _context.Nichoirs
                .FirstOrDefaultAsync(m => m.id_nichoir == id);
            if (nichoir == null)
            {
                return NotFound();
            }

            return View(nichoir);
        }

        // GET: Nichoirs/Create
        public IActionResult Create()
        {
            return View();
        }

        // POST: Nichoirs/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("id_nichoir,nom,emplacement,description,date_ajout,statut_batterie,statut_pir,statut_led_ir,resolution_camera")] Nichoir nichoir)
        {
            if (ModelState.IsValid)
            {
                _context.Add(nichoir);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            return View(nichoir);
        }

        // GET: Nichoirs/Edit/5
        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var nichoir = await _context.Nichoirs.FindAsync(id);
            if (nichoir == null)
            {
                return NotFound();
            }
            return View(nichoir);
        }

        // POST: Nichoirs/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int id, [Bind("id_nichoir,nom,emplacement,description,date_ajout,statut_batterie,statut_pir,statut_led_ir,resolution_camera")] Nichoir nichoir)
        {
            if (id != nichoir.id_nichoir)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(nichoir);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!NichoirExists(nichoir.id_nichoir))
                    {
                        return NotFound();
                    }
                    else
                    {
                        throw;
                    }
                }
                return RedirectToAction(nameof(Index));
            }
            return View(nichoir);
        }

        // GET: Nichoirs/Delete/5
        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var nichoir = await _context.Nichoirs
                .FirstOrDefaultAsync(m => m.id_nichoir == id);
            if (nichoir == null)
            {
                return NotFound();
            }

            return View(nichoir);
        }

        // POST: Nichoirs/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(int id)
        {
            var nichoir = await _context.Nichoirs.FindAsync(id);
            if (nichoir != null)
            {
                _context.Nichoirs.Remove(nichoir);
            }

            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool NichoirExists(int id)
        {
            return _context.Nichoirs.Any(e => e.id_nichoir == id);
        }
    }
}
