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

function calculate() {
    // Calculation
    const weapon = document.querySelector('input[name="weapon"]:checked').value
    const structure = document.querySelector('input[name="structureType"]:checked').value
    const hp = parseFloat(document.getElementById('structure-hp').value) || 0
    const cave = document.querySelector('input[name="caveDamage"]:checked').value === "caveDamageYes"
    let quality = parseFloat(document.getElementById('tek-rifle-quality').value) || 100

    let damage = damageTable[weapon][structure]
    if (weapon === "tekRifle") {
        if (quality < 100) quality = 100
        if (quality > 200) quality = 200
        damage *= quality / 100.0
    }

    if (damage <= 0) {
        console.info(`${weapon} cannot destroy ${structure}.`)
        updateResourceOutput({})
        
        document.getElementById('output-amount-indestructible').style.display = 'block'
        document.getElementById('resource-indestructible').style.display = 'flex'
        document.getElementById('output-amount-group').style.display = 'none'
        return
    }

    document.getElementById('output-amount-indestructible').style.display = 'none'
    document.getElementById('resource-indestructible').style.display = 'none'
    document.getElementById('output-amount-group').style.display = 'block'

    if (cave) damage *= 6

    const amount = Math.ceil(hp / damage)

    // Calculate resource cost
    const bngMode = document.getElementById('bng-mode').checked

    let baseCostFunc = craftingCosts[weapon]
    if (!baseCostFunc) {
        updateResourceOutput({})
        return
    }

    let cost = baseCostFunc(bngMode)
    let costAmount = weapon === 'tekGrenade' ? Math.ceil(amount / 3) : amount
    const result = {}
    for (const [res, val] of Object.entries(cost)) {
        const key = res.replace(/([A-Z])/g, '-$1').toLowerCase()
        result[key] = Math.ceil(val * (res === "element" ? costAmount : costAmount))
    }

    // Output
    console.info(`Weapon: ${weapon} | Structure: ${structure} | HP: ${hp} | Cave 6x: ${cave ? 'Yes' : 'No'} | Damage per hit: ${damage.toFixed(0)} | => ${amount} shots`)

    updateResourceOutput(result)
    document.getElementById('output-amount').textContent = amount.toString()
    document.getElementById('output-damage').textContent = damage.toFixed(0).toString()
}

function updateResourceOutput(resourceMap) {
    const resourceIds = [
        'cementing-paste', 'crystal', 'electronics', 'element', 'fiber',
        'gunpowder', 'hide', 'metal-ingot', 'obsidian', 'oil',
        'polymer', 'stone'
    ]

    for (const id of resourceIds) {
        const col = document.getElementById(`resource-${id}`)
        const h3 = col.querySelector('h3')
        const mapKey = id.replace(/-/g, '')
        const value = resourceMap[mapKey] ?? 0

        if (value > 0) {
            h3.textContent = value
            col.classList.remove('d-none')
        } else {
            h3.textContent = ''
            col.classList.add('d-none')
        }
    }
}


function toggleTekRifleFields() {
    const isSelected = tekRifleRadio.checked
    tekRifleLabel.style.display = isSelected ? "none" : "block"
    tekRifleQuality.style.display = isSelected ? "flex" : "none"
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

// Call calculate
document.querySelectorAll('input').forEach((el) => {
    el.addEventListener("change", calculate)
})

calculate()
