using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
public class InventorySpawnner : MonoBehaviour{
    public GameObject[] models;
    public GameObject panel;
    Image panelImageScript;
    Image biographyImageScript;
    public GameObject[] buttonReferences;
    [HideInInspector]
    public List<GameObject> buttons;
    int triggerSquareBoundary;
    [HideInInspector]
    public bool changeInventoryIcons;
    public enum InventoryDisplayStates { NoInventory, InventoryTorsoSpawning, InventoryTorsoSpawningDone, InventoryLegsSpawning, InventoryLegsSpawningDone }
    [HideInInspector]
    public InventoryDisplayStates inventoryDisplayStates;
    public enum ButtonStates { Create, Delete }
    [HideInInspector]
    public ButtonStates buttonStates;
    string[] torsoItems;
    string[] legsItems;
    [HideInInspector]
    public Collider modelCollider;

    void Start()
    {
        buttons = new List<GameObject>();
        panelImageScript = panel.GetComponent<Image>();
        biographyImageScript = GameObject.Find("Biography").GetComponent<Image>();
        triggerSquareBoundary = 5;
        changeInventoryIcons = false;
        inventoryDisplayStates = InventoryDisplayStates.NoInventory;
        buttonStates = ButtonStates.Create;
        torsoItems = new string[] { "Blouse", "Jacket", "Shirt", "Tank" };
        legsItems = new string[] { "Miniskirt", "Shorts", "Pants", "Dress" };
    }

    void Update()
    {
        if (changeInventoryIcons && inventoryDisplayStates == InventoryDisplayStates.InventoryLegsSpawning)
        {
            for (int i = 0; i < buttons.Count; i++)
            {
                buttons[i].GetComponent<Image>().sprite = Resources.Load<Sprite>("Sprites/LegsItems/" + legsItems[i]);
            }
            inventoryDisplayStates = InventoryDisplayStates.InventoryLegsSpawningDone;
            changeInventoryIcons = false;
        }
        if (buttonStates == ButtonStates.Delete)
        {
            biographyImageScript.color = Color.clear;
            panelImageScript.color = Color.clear;
            changeInventoryIcons = false;
            inventoryDisplayStates = InventoryDisplayStates.NoInventory;
            buttonStates = ButtonStates.Create;
            DestroyButtons();
        }
    }

    void OnTriggerEnter(Collider other)
    {
        modelCollider = other;
        if (other.tag == "models")
        {
            panelImageScript.color = Color.white;
            if (inventoryDisplayStates == InventoryDisplayStates.NoInventory)
            {
                SpawnButtons();
                inventoryDisplayStates = InventoryDisplayStates.InventoryTorsoSpawning;
            }
            if (inventoryDisplayStates == InventoryDisplayStates.InventoryTorsoSpawning)
            {
                for (int i = 0; i < buttons.Count; i++)
                {
                    buttons[i].GetComponent<Image>().sprite = Resources.Load<Sprite>("Sprites/TorsoItems/" + torsoItems[i]);
                }
                inventoryDisplayStates = InventoryDisplayStates.InventoryTorsoSpawningDone;
            }
        }
        if(other.name == "Jenni")
        {
            biographyImageScript.sprite= Resources.Load<Sprite>("Biography/biographs/bio1");
            biographyImageScript.color = Color.white;
        }
        else if(other.name == "Andrew")
        {
            biographyImageScript.sprite = Resources.Load<Sprite>("Biography/biographs/bio2");
            biographyImageScript.color = Color.white;
        }
        else if (other.name == "Melissa")
        {
            biographyImageScript.sprite = Resources.Load<Sprite>("Biography/biographs/bio3");
            biographyImageScript.color = Color.white;
        }
        else if (other.name == "Julian")
        {
            biographyImageScript.sprite = Resources.Load<Sprite>("Biography/biographs/bio4");
            biographyImageScript.color = Color.white;
        }
    }
    //void OnTriggerExit(Collider other)
    //{
    //    if (other.tag == "models")
    //    {
    //        biographyImageScript.color = Color.clear;
    //        panelImageScript.color = Color.clear;
    //        changeInventoryIcons = false;
    //        inventoryDisplayStates = InventoryDisplayStates.NoInventory;
    //        buttonStates = ButtonStates.Create;
    //        DestroyButtons();
    //    }
    //}

    public void clearDisplay()
    {
        biographyImageScript.color = Color.clear;
        panelImageScript.color = Color.clear;
        changeInventoryIcons = false;
        inventoryDisplayStates = InventoryDisplayStates.NoInventory;
        buttonStates = ButtonStates.Create;
        DestroyButtons();
    }
    void SpawnButtons()
    {
        for (int i = 0; i < buttonReferences.Length; i++)
        {
            GameObject button = Instantiate(buttonReferences[i] as GameObject);
            button.transform.SetParent(panel.transform);
            button.transform.position = panel.transform.position;
            button.transform.localScale = Vector3.one;
            button.transform.rotation = panel.transform.rotation;
            buttons.Add(button);
        }
    }
    public void DestroyButtons()
    {
        for (int i = 0; i < buttons.Count; i++)
        {
            Destroy(buttons[i]);
        }
        buttons.Clear();
    }
}
