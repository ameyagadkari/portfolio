using UnityEngine;
using System.Collections;

public class InventoryChanger : MonoBehaviour {
    InventorySpawnner inventorySpawnnerScript;
    talk1 talk1Script;
    public int dressSelect;
    public static bool isTorsoCovered = false;

    //talk1 talk_ref = null;
    void Start()
    {
        inventorySpawnnerScript = GameObject.Find("FashionPolice").GetComponent<InventorySpawnner>();
        talk1Script = GameObject.Find(inventorySpawnnerScript.modelCollider.name).GetComponent<talk1>();
        //talk1 = GameObject.Find)(
    }
    public void ChangeInventory(int dressSelect)
    {
        this.dressSelect = dressSelect;        
        if(inventorySpawnnerScript.inventoryDisplayStates==InventorySpawnner.InventoryDisplayStates.InventoryTorsoSpawningDone )
        {
            talk1Script.ChangeTorso(dressSelect);
            inventorySpawnnerScript.inventoryDisplayStates = InventorySpawnner.InventoryDisplayStates.InventoryLegsSpawning;
            inventorySpawnnerScript.changeInventoryIcons = true;
        }
        else if (inventorySpawnnerScript.inventoryDisplayStates == InventorySpawnner.InventoryDisplayStates.InventoryLegsSpawningDone && (isTorsoCovered))
        {
            talk1Script.ChangeLegs(dressSelect);
            inventorySpawnnerScript.buttonStates = InventorySpawnner.ButtonStates.Delete;
        }
    }
}