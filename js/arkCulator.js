const damageTable = {
    c4: {wood:11813, stone:99999, metal:3544, tek:788},
    cannon: {wood:99999, stone:3446, metal:355, tek:40},
    catapult: {wood:15750, stone:700, metal:0, tek:0},
    grenade: {wood:788, stone:1838, metal:237, tek:53},
    rocketLauncher: {wood:7350, stone:99999, metal:2205, tek:596},
    tekGrenade: {wood:1115, stone:612, metal:59, tek:385},
    tekRifle: {wood:536, stone:294, metal:29, tek:185}
}

const craftingCosts = {
    c4: (bng) => ({
        gunpowder: bng ? 300 : 60,
        crystal: bng ? 50 : 10,
        cementingPaste: bng ? 25 : 5,
        fiber: bng ? 250 : 50,
        hide: bng ? 25 : 5,
        polymer: bng ? 25 : 5,
        electronics: bng ? 25 : 5
    }),
    cannon: () => ({
        metalIngot: 80,
        gunpowder: 30,
        cementingPaste: 20,
        obsidian: 4
    }),
    catapult: () => ({
        stone: 30,
        metalIngot: 3
    }),
    grenade: () => ({
        fiber: 15,
        stone: 20,
        gunpowder: 30,
        hide: 5,
        metalIngot: 2,
        oil: 4
    }),
    rocketLauncher: () => ({
        gunpowder: 40,
        crystal: 10,
        cementingPaste: 20,
        polymer: 10,
        metalIngot: 12
    }),
    tekGrenade: () => ({
        element: 1,
        crystal: 40,
        cementingPaste: 10,
        metalIngot: 30,
        polymer: 30,
        gunpowder: 60
    }),
    tekRifle: () => ({
        element: 0.02
    })
}

const resources = {
    cementingPaste: (bng) => ({
        stackSize: bng ? 999999999 : 100,
        wikiUrl: 'https://ark.wiki.gg/wiki/Cementing_Paste'
    }),
    crystal: (bng) => ({
        stackSize: bng ? 999999999 : 100,
        wikiUrl: 'https://ark.wiki.gg/wiki/Crystal'
    }),
    electronics: (bng) => ({
        stackSize: bng ? 999999999 : 100,
        wikiUrl: 'https://ark.wiki.gg/wiki/Electronics'
    }),
    element: (bng) => ({
        stackSize: bng ? 999999999 : 100,
        wikiUrl: 'https://ark.wiki.gg/wiki/Element'
    }),
    fiber: (bng) => ({
        stackSize: bng ? 999999999 : 300,
        wikiUrl: 'https://ark.wiki.gg/wiki/Fiber'
    }),
    gunpowder: (bng) => ({
        stackSize: bng ? 999999999 : 100,
        wikiUrl: 'https://ark.wiki.gg/wiki/Gunpowder'
    }),
    hide: (bng) => ({
        stackSize: bng ? 999999999 : 200,
        wikiUrl: 'https://ark.wiki.gg/wiki/Hide'
    }),
    metalIngot: (bng) => ({
        stackSize: bng ? 999999999 : 300,
        wikiUrl: 'https://ark.wiki.gg/wiki/Metal_Ingot'
    }),
    obsidian: (bng) => ({
        stackSize: bng ? 999999999 : 100,
        wikiUrl: 'https://ark.wiki.gg/wiki/Obsidian'
    }),
    oil: (bng) => ({
        stackSize: bng ? 999999999 : 100,
        wikiUrl: 'https://ark.wiki.gg/wiki/Oil'
    }),
    polymer: (bng) => ({
        stackSize: bng ? 999999999 : 100,
        wikiUrl: 'https://ark.wiki.gg/wiki/Polymer'
    }),
    stone: (bng) => ({
        stackSize: bng ? 999999999 : 100,
        wikiUrl: 'https://ark.wiki.gg/wiki/Stone'
    }),
}

function update() {
    const weapon = document.querySelector('input[name="weapon"]:checked').value
    const structure = document.querySelector('input[name="structureType"]:checked').value
    const bngMode = document.getElementById('bng-mode').checked
    const cave = document.querySelector('input[name="caveDamage"]:checked').value === "caveDamageYes"

    // HP input validation
    let hp = parseFloat(document.getElementById('structure-hp').value) || 0
    if (hp > 99999999) hp = 99999999
    if (hp <= 0) hp = 1
    document.getElementById('structure-hp').value = hp

    // Quality input validation
    let quality = parseFloat(document.getElementById('tek-rifle-quality').value) || 100
    if (quality < 100) quality = 100
    if (quality > 200) {
        quality = 200
        document.getElementById('tek-rifle-quality').value = quality
    }

    const { damage, shots, resources } = calculateCostForWeapon(
        weapon,
        structure,
        hp,
        bngMode,
        cave,
        quality
    )

    const isIndestructible = damage <= 0

    document.getElementById('output-amount-indestructible').style.display = isIndestructible ? 'block' : 'none'
    document.getElementById('resource-indestructible').style.display = isIndestructible ? 'flex' : 'none'
    document.getElementById('output-amount-group').style.display = isIndestructible ? 'none' : 'block'

    if (!isIndestructible) {
        document.getElementById('output-amount').textContent = shots
        document.getElementById('output-damage').textContent = damage.toFixed(0)
    }

    updateResourceOutput(resources, bngMode)

    console.info(`Weapon: ${weapon} | Structure: ${structure} | HP: ${hp} | Cave 6x: ${cave ? 'Yes' : 'No'} | Damage per hit: ${damage.toFixed(0)} | => ${shots} shots`)
}

function calculateCostForWeapon(weapon, structure, hp, bngMode, cave, quality = 100) {
    let damage = damageTable[weapon]?.[structure] ?? 0

    if (weapon === 'tekRifle') {
        quality = Math.min(200, Math.max(100, quality))
        damage *= quality / 100
    }

    if (damage <= 0) return { damage: 0, shots: 0, resources: {} }

    if (cave) damage *= 6

    let shots = Math.ceil(hp / damage)
    if (shots < 1) shots = 1
    const costFn = craftingCosts[weapon]
    if (!costFn) return { damage, shots, resources: {} }

    const cost = costFn(bngMode)
    const effectiveShots = weapon === 'tekGrenade' ? Math.ceil(shots / 3) : shots

    const resources = Object.fromEntries(
        Object.entries(cost).map(([res, val]) => [res, Math.ceil(val * effectiveShots)])
    )

    return { damage, shots, resources }
}

function updateResourceOutput(resourceMap, bngMode) {
    for (const [id, getResourceData] of Object.entries(resources)) {
        const col = document.getElementById(`resource-${id}`)
        if (!col) continue

        const h3 = col.querySelector('h3')
        const infoSpan = col.querySelector('p.my-0.text-muted')
        const value = resourceMap[id] ?? 0

        const { stackSize } = getResourceData(bngMode)


        if (value > 0) {
            h3.textContent = value

            const stacks = Math.floor(value / stackSize)
            const rest = value % stackSize

            if (stacks >= 1) {
                const stackWord = stacks === 1 ? 'stack' : 'stacks'
                let text = `${stacks} ${stackWord}`
                if (rest > 0) {
                    text += ` +${rest}`
                }
                infoSpan.textContent = `(${text})`
                infoSpan.parentElement.style.display = 'block'
            } else {
                infoSpan.textContent = ''
                infoSpan.parentElement.style.display = 'none'
            }

            col.classList.remove('d-none')
        } else {
            h3.textContent = ''
            if (infoSpan) infoSpan.parentElement.style.display = 'none'
            col.classList.add('d-none')
        }
    }
}

function toggleTekRifleFields() {
    const isSelected = tekRifleRadio.checked
    tekRifleLabel.style.display = isSelected ? "none" : "block"
    tekRifleQuality.style.display = isSelected ? "flex" : "none"
}

function initializeResourceImages() {
    for (const [id, getResourceData] of Object.entries(resources)) {
        const col = document.getElementById(`resource-${id}`)
        if (!col) continue

        const img = col.querySelector('img')
        if (!img) continue

        const { wikiUrl } = getResourceData(false)
        if (wikiUrl) {
            img.setAttribute('onclick', `window.open('${wikiUrl}', '_blank')`)
        }
    }
}


// Tek rifle quality swap
const tekRifleRadio = document.getElementById("weapon-tek-rifle")
const tekRifleLabel = document.getElementById("tek-rifle-label")
const tekRifleQuality = document.getElementById("tek-rifle-quality-group")

toggleTekRifleFields()
tekRifleRadio.addEventListener("change", toggleTekRifleFields)

document.querySelectorAll('input[name="weapon"]').forEach((el) => {
    el.addEventListener("change", toggleTekRifleFields)
})


// Call update()
document.querySelectorAll('input').forEach((el) => {
    el.addEventListener("input", update)
})


update()
initializeResourceImages()
